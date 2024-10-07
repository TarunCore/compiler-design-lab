set ns [new Simulator]
set nodes [list]
for {set i 0} {$i < 7} {incr i} {
 lappend nodes [$ns node]
}
foreach node1 $nodes {
 foreach node2 $nodes {
 if {[lsearch -exact $nodes $node1] < [lsearch -exact $nodes
$node2]} {
 $ns duplex-link $node1 $node2 1Mb 10ms DropTail
 }
 }
}
set tracefile [open out-mesh.tr w]
$ns trace-all $tracefile
set nf [open out-mesh.nam w]
$ns namtrace-all $nf
proc finish {} {
 global ns tracefile nf
 $ns flush-trace
 close $nf
 close $tracefile
 exec nam out-mesh.nam &
 exit 0
}
$ns at 5.0 "finish"
$ns run