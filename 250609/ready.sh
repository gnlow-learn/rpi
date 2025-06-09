cd /sys/class/sysprog_gpio

inn() {
    local pin=$1

    echo "$pin" > export
    echo in > gpio$pin/direction
}
out() {
    local pin=$1
    local value=${2:-0}  # 기본값은 0

    echo "$pin" > export
    echo out > gpio$pin/direction
    echo "$value" > gpio$pin/value
}

inn 17
inn 19

out 26
out 27
