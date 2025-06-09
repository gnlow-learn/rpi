ip=$1
host=http://192.168.0.$ip:8000

curl $host/main.c -o main.c
curl $host/gpio.c -o gpio.c
bash run.sh main
