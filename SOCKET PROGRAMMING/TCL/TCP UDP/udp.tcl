set ns [new Simulator]
$ns color 1 Blue
$ns color 2 Red
set tracefile [open out.tr w]
$ns trace-all $tracefile
set nf [open out.nam w]
$ns namtrace-all $nf
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n0 $n3 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n3 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set tcpsink [new Agent/TCPSink]
$ns attach-agent $n1 $tcpsink
$ns connect $tcp $tcpsink
$tcp set fid_ 1
set ftp [new Application/FTP]
$ftp attach-agent $tcp
set udp [new Agent/UDP]
$ns attach-agent $n2 $udp
set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
$udp set fid_ 2
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
proc finish {} {
global ns tracefile nf
$ns flush-trace
close $nf
close $tracefile
exec nam out.nam &
exit 0
}
$ns at 1.0 "$ftp start"
$ns at 2.0 "$ftp stop"
$ns at 1.0 "$cbr start"
$ns at 2.0 "$cbr stop"
$ns at 5.0 "finish"
$ns run