set ns [new Simulator]

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail

set tracefile [open out.tr w]
$ns trace-all $tracefile
set nf [open out.nam w]
$ns trace-all $nf

proc finish {} {
    global ns tracefile nf
    $ns flush-trace
    close $nf
    close $tracefile
    exec nam out.nam &
    exit 0
}
$ns at 5.0 "finish"
$ns run