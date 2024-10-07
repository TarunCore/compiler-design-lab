set ns [new Simulator]
set centralNode [$ns node]
set nodes [list]
for {set i 0} {$i < 6} {incr i} {
 set node [$ns node]
 lappend nodes $node
 $ns duplex-link $centralNode $node 1Mb 10ms DropTail
}
set tracefile [open out-star.tr w]
$ns trace-all $tracefile
set nf [open out-star.nam w]
$ns namtrace-all $nf
proc finish {} {
 global ns tracefile nf
 $ns flush-trace
 close $nf
 close $tracefile
 exec nam out-star.nam &
 exit 0
}
$ns at 5.0 "finish"
$ns run
