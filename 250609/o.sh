ip=$1
host=http://192.168.0.$ip:8000

while read -r file; do
    echo "Download $host/$file"
    curl $host/$file -o $file
done < <(sed 's/\r$//' <(curl $host/.include))
