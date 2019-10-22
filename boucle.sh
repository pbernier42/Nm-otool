#!/bin/bash
all_test=$(ls -R ./break-nm-master/feed_the_nm/*)
make ft_otool

for file in $all_test; do
	otool -t $file > .real
	./ft_otool -t $file > .mine
	echo "[$file]"

	ret=$(diff .real .mine)
	if [[ ! -z $ret  ]]; then
		read
		./ft_otool -t $file
		# diff -y .real .mine
	fi

done
