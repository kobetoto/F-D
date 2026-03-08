#!/bin/bash

#v1
#while ./PMerge $(shuf -i 1-1000 -n 1000) > pmerge2.txt; do :; done

#v2
#i=0; while ./PMerge $(shuf -i 1-1000 -n 1000) > pmerge2.txt; do ((i++)); echo "OK $i"; done

#v3
# i=0
# while ./PMerge $(shuf -i 1-2 -n 51) >> pmerge.txt; do
#   ((i++))
#   printf "\rOK %d" "$i"
# done
# echo

#v4
# range=$1
# count=$2
# # range=${1:-1-11}
# # count=${2:-10}
#
# if [ -z "$range" ] || [ -z "$count" ]; then
# 	echo "Usage: $0 <range> <count>"
# 	echo "Exemple: $0 1-100 101"
# 	exit 1
# fi
#
# i=0
# while ./PMerge $(shuf -i "$range" -n "$count") >> pmerge.txt; do
# 	((i++))
# 	printf "\rOK %d" "$i"
# done
# echo

#v5
# ===== Parameters =====
# range=$1
# count=$2
# max_tests=${3:-0} #0 = infinite
# threads=${4:-1}
# outfile=${5:-pmerge.txt}
#
# echo "Range: $range"
# echo "Count: $count"
# echo "Max tests: $max_tests"
# echo "Threads: $treads"
#
# if [ -z "$range" ] || [ -z "$count" ]; then
# 	echo "Usage: $0 <range> <count>"
# 	echo "Exemple: $0 1-100 101"
# 	exit 1
# fi
#
# run_test()
# {
# 	local i=0
# 	while true; do
# 		./PMerge $(shuf -i "$range" -n "$count") >> "$outfile"
# 		if [ $? -ne 0 ]; then
# 			echo "Error detected after $i tests"
# 			exit 1
# 		fi
# 		((i++))
#
# 		printf "\rOK %d" "$i"
#
# 		if [ "$max_tests" -ne 0 ] && [ "$i" -ge "$max_tests" ]; then
# 			break
# 		fi
# 	done
# 	echo
# }
#
# pids=()
# for ((j=0; j<threads; j++)); do
# 	run_test &
# 	pids+=($!)
# done
#
# wait "${pids[@]}"
#
# echo "Tests done"

#v6
# export LC_ALL=C
# # ===== Parameters =====
# range=$1
# count=$2
# max_tests=${3:-0} #0 = infinite
# outfile=${5:-pmerge.txt}
#
# echo "Range: $range"
# echo "Count: $count"
#
# if [ -z "$range" ] || [ -z "$count" ]; then
# 	echo "Usage: $0 <range> <count>"
# 	echo "Exemple: $0 1-100 101"
# 	exit 1
# fi
#
# #empty file
# > "$outfile"
#
# i=0
# while true; do
# 	./PMerge $(shuf -i "$range" -n "$count") >> "$outfile"
# 	if [ $? -ne 0 ]; then
# 		echo "Error detected after $i tests"
# 		exit 1
# 	fi
# 	((i++))
#
# 	printf "\rOK %d" "$i"
#
# 	if [ "$max_tests" -ne 0 ] && [ "$i" -ge "$max_tests" ]; then
# 		break
# 	fi
# done
# echo
#
# # ===== stats =====
# if [ "$max_tests" -ne 0 ]; then
# 	LC_ALL=C awk '
# 	/std::vector:/ {
# 	  split($0,a,"vector:");
# 	  split(a[2],b," ");
# 	  vect_time += b[1];
# 	  vect_n++;
# 	}
# 	/std::list:/ {
# 	  split($0,a,"list:");
# 	  split(a[2],b," ");
# 	  list_time += b[1];
# 	  list_n++;
# 	}
# 	/vect comp:/ {
# 	  split($0,a,":");
# 	  vect_comp += a[2];
# 	  vectc_n++;
# 	}
# 	/list comp:/ {
# 	  split($0,a,":");
# 	  list_comp += a[2];
# 	  listc_n++;
# 	}
# 	/maxComp:/ {
# 	  split($0,a,":");
# 	  max_comp = a[2];
# 	}
# 	END {
# 	  print "===== RESULTATS =====";
#
# 	  if (vect_n > 0)
# 		printf("Vector time avg: %.6f ms\n", vect_time/vect_n);
#
# 	  if (list_n > 0)
# 		printf("List time avg: %.6f ms\n", list_time/list_n);
#
# 	  if (vectc_n > 0)
# 		printf("Vector comp avg: %.2f\n", vect_comp/vectc_n);
#
# 	  if (listc_n > 0)
# 		printf("List comp avg: %.2f\n", list_comp/listc_n);
#
# 	  print "Max comparisons:", max_comp;
# 	}
# 	' "$outfile"
# fi

#v7
export LC_ALL=C
# ===== Parameters =====
range=$1
count=$2
max_tests=${3:-0} #0 = infinite
outfile=${4:-pmerge.txt}

echo "Range: $range"
echo "Count: $count"

if [ -z "$range" ] || [ -z "$count" ]; then
	echo "Usage: $0 <range> <count>"
	echo "Exemple: $0 1-100 101"
	exit 1
fi

#empty file
> "$outfile"

i=0
while true; do
	ex02/PmergeMe $(shuf -i "$range" -n "$count") >> "$outfile"
	if [ $? -ne 0 ]; then
		echo "Error detected after $i tests"
		exit 1
	fi
	((i++))

	printf "\rOK %d" "$i"

	if [ "$max_tests" -ne 0 ] && [ "$i" -ge "$max_tests" ]; then
		break
	fi
done
echo

# ===== stats =====
if [ "$max_tests" -ne 0 ]; then
LC_ALL=C awk '
/std::vector:/ {
  split($0,a,"vector:");
  split(a[2],b," ");
  val = b[1] + 0;

  vect_sum += val;
  vect_n++;

  if (vect_n == 1 || val < vect_min) vect_min = val;
  if (vect_n == 1 || val > vect_max) vect_max = val;
}

/std::list:/ {
  split($0,a,"list:");
  split(a[2],b," ");
  val = b[1] + 0;

  list_sum += val;
  list_n++;

  if (list_n == 1 || val < list_min) list_min = val;
  if (list_n == 1 || val > list_max) list_max = val;
}

/vect comp:/ {
  split($0,a,":");
  val = a[2] + 0;

  vectc_sum += val;
  vectc_n++;

  if (vectc_n == 1 || val < vectc_min) vectc_min = val;
  if (vectc_n == 1 || val > vectc_max) vectc_max = val;
}

/list comp:/ {
  split($0,a,":");
  val = a[2] + 0;

  listc_sum += val;
  listc_n++;

  if (listc_n == 1 || val < listc_min) listc_min = val;
  if (listc_n == 1 || val > listc_max) listc_max = val;
}

/maxComp:/ {
  split($0,a,":");
  max_comp = a[2];
}

END {
  print "===== RESULTATS =====";

  if (vect_n > 0) {
    printf("Vector time avg: %.6f ms\n", vect_sum/vect_n);
    printf("Vector time min: %.6f ms\n", vect_min);
    printf("Vector time max: %.6f ms\n", vect_max);
  }

  if (list_n > 0) {
    printf("List time avg: %.6f ms\n", list_sum/list_n);
    printf("List time min: %.6f ms\n", list_min);
    printf("List time max: %.6f ms\n", list_max);
  }

  if (vectc_n > 0) {
    printf("Vector comp avg: %.2f\n", vectc_sum/vectc_n);
    printf("Vector comp min: %d\n", vectc_min);
    printf("Vector comp max: %d\n", vectc_max);
  }

  if (listc_n > 0) {
    printf("List comp avg: %.2f\n", listc_sum/listc_n);
    printf("List comp min: %d\n", listc_min);
    printf("List comp max: %d\n", listc_max);
  }

  print "Max comparisons allowed:", max_comp;
}
' "$outfile"
fi
