#!/bin/bash

dir="tests/ls"
dir2="tests/ftls"

mkdir -p $dir
mkdir -p $dir2

ls_files=(
	"ls"
	"ls-a"
	"ls-l"
	"ls-r"
	"ls-R_"
	"ls-t"
	"ls-al"
	"ls-aR"
	"ls-ar"
	"ls-at"
	"ls-lR"
	"ls-lr"
	"ls-lt"
	"ls-Rr"
	"ls-Rt"
	"ls-rt"
	"ls-alR"
	"ls-alr"
	"ls-alt"
	"ls-aRr"
	"ls-aRt"
	"ls-art"
	"ls-lRr"
	"ls-lRt"
	"ls-lrt"
	"ls-Rrt"
	"ls-alRr"
	"ls-alRt"
	"ls-alrt"
	"ls-aRrt"
	"ls-lRrt"
	"ls-alRrt"
)
ls_flags=(
	""
	"-a"
	"-l"
	"-r"
	"-R"
	"-t"
	"-al"
	"-aR"
	"-ar"
	"-at"
	"-lR"
	"-lr"
	"-lt"
	"-Rr"
	"-Rt"
	"-rt"
	"-alR"
	"-alr"
	"-alt"
	"-aRr"
	"-aRt"
	"-art"
	"-lRr"
	"-lRt"
	"-lrt"
	"-Rrt"
	"-alRr"
	"-alRt"
	"-alrt"
	"-aRrt"
	"-lRrt"
	"-alRrt"
)

# Colors
green=$'\033[0;32m'
red=$'\033[0;31m'
reset=$'\033[0;39m'

run_test() {
	if diff -q "$1" "$2" >/dev/null; then
		echo -e "${green}$3\t\tOK${reset}"
	else
		echo -e "${red}$3\t\tKO${reset}"
	fi
}

generate_ls_output() {
	local output_file="$1"
	local flags="$2"
	ls $flags > "$output_file"
}

generate_ft_ls_output() {
	local output_file="$1"
	local flags="$2"
	./ft_ls $flags > "$output_file"
}

# Generate ls output files
for ((i = 0; i < ${#ls_files[@]}; i++)); do
	generate_ls_output "$dir/${ls_files[i]}" "${ls_flags[i]}"
done

# Generate ft_ls output files
for ((i = 0; i < ${#ls_files[@]}; i++)); do
	generate_ft_ls_output "$dir2/${ls_files[i]}" "${ls_flags[i]}"
done

# Run tests
for ((i = 0; i < ${#ls_files[@]}; i++)); do
	run_test "$dir/${ls_files[i]}" "$dir2/${ls_files[i]}" "${ls_flags[i]}"
done