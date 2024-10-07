set ns [new Simulator]
$ns color 1 Blue
$ns color 2 Red
set nf [open tarun_22BCE2505.nam w]
$ns namtrace-all $nf
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0
$tcp0 set fid_ 1
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set sink1 [new Agent/Null]
$ns attach-agent $n3 $sink1
$ns connect $udp1 $sink1
$udp1 set fid_ 2
set ftp [new Application/FTP]
$ftp attach-agent $tcp0
$ftp set type_ FTP
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp1
$cbr set packet_size_ 500
$cbr set rate_ 1Mb
$ns at 0.1 "$ftp start"
$ns at 0.2 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 5.0 "$ftp stop"
$ns at 6.0 "finish"
proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam tarun_22BCE2505.nam &
exit 0
}