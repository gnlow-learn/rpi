name=$1

gcc "$name.c" -o "$name" && ./$name && rm -f "$name"
