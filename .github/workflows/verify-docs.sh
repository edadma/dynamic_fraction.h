#!/bin/bash

# Documentation verification script for CI/CD

set -e

echo "🔍 Verifying documentation generation..."

# Check that critical files exist
CRITICAL_FILES=(
    "docs/html/index.html"
    "docs/html/dynamic__fraction_8h.html"
    "docs/html/annotated.html"
    "docs/html/files.html"
)

for file in "${CRITICAL_FILES[@]}"; do
    if [[ ! -f "$file" ]]; then
        echo "❌ Critical file missing: $file"
        exit 1
    fi
    echo "✅ Found: $file"
done

# Check for excessive warnings
if [[ -f "doxygen_warnings.log" ]]; then
    warning_count=$(wc -l < doxygen_warnings.log)
    echo "📊 Documentation warnings: $warning_count"

    # Allow up to 10 warnings (configurable threshold)
    MAX_WARNINGS=10
    if [[ $warning_count -gt $MAX_WARNINGS ]]; then
        echo "❌ Too many documentation warnings ($warning_count > $MAX_WARNINGS)"
        echo "Recent warnings:"
        head -20 doxygen_warnings.log
        exit 1
    fi

    if [[ $warning_count -gt 0 ]]; then
        echo "⚠️ Warning details:"
        cat doxygen_warnings.log
    fi
else
    echo "✅ No warning log found (clean build)"
fi

# Check that main sections exist
if ! grep -q "Dynamic Fraction Library" docs/html/index.html; then
    echo "❌ Main project title not found in documentation"
    exit 1
fi

echo "🎉 Documentation verification completed successfully!"
echo "📈 Generated $(find docs/html -name "*.html" | wc -l) HTML files"

# Optional: Check for broken links (requires additional tools)
# This can be extended with link checkers in the future