all_test=$(ls -R ./break-nm-master/feed_the_nm/*)
longueur_mini=750

for file in ${all_test}; do
	./test.sh -t ${file} > tmp
	content=$(cat -s tmp)
	if [ "${#content}" -lt "$longueur_mini" ]; then
		echo ${file}
		array=($(echo $content | tr '\r' "\n"))
		echo "${array[53]}"
		# for index in "${!array[@]}"
		# do
    	# 	echo "$index ${array[index]}"
		# done
	fi
	#rm tmp
done
