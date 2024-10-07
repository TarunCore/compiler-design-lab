set ns [new Simulator]
set nodes [list]
for {set i 0} {$i < 6} {incr i} {
 lappend nodes [$ns node]
}
for {set i 0} {$i < 5} {incr i} {
 $ns duplex-link [lindex $nodes $i] [lindex $nodes [expr $i + 1]]
1Mb 10ms DropTail
}
set tracefile [open out-bus.tr w]
$ns trace-all $tracefile
set nf [open out-bus.nam w]
$ns namtrace-all $nf
proc finish {} {
 global ns tracefile nf
 $ns flush-trace
 close $nf
 close $tracefile
 exec nam out-bus.nam &
 exit 0
}
$ns at 5.0 "finish"
$ns run