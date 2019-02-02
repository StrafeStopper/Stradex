read build_number_w < settings/build_number_w.txt
build_number_w=$((build_number_w+1))

echo "$build_number_w" > "settings/build_number_w.txt"
