set ns [new Simulator]
set nodes [list]
for {set i 0} {$i < 5} {incr i} {
 lappend nodes [$ns node]
}
for {set i 0} {$i < 5} {incr i} {
 set next [expr ($i + 1) % 5]
 $ns duplex-link [lindex $nodes $i] [lindex $nodes $next] 1Mb
10ms DropTail
}
set tracefile [open out-ring.tr w]
$ns trace-all $tracefile
set nf [open out-ring.nam w]
$ns namtrace-all $nf
proc finish {} {
 global ns tracefile nf
 $ns flush-trace
 close $nf
 close $tracefile
 exec nam out-ring.nam &
 exit 0
}
$ns at 5.0 "finish"
$ns run