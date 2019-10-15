use strict;
use warnings;

my $length = 100;
$length = $ARGV[0] if ($#ARGV == 0);

my ($inertia, @circuit) = &makeRollerCoaster($length);
my ($H, $W, @map) = &buildMap (@circuit);

&printMap ($inertia, $H, $W, @map);

# ----------------------------------------------------------------

sub buildMap
{
    my (@circuit) = @_;
    my @tmp;
    my $previous_slope = $circuit[0];
    push @tmp, $previous_slope;
    foreach my $i_slope (1..$#circuit)
    {
        my $slope = $circuit[$i_slope];
        
        if (($previous_slope eq '\\') and ($slope eq '/'))  
        {
            push @tmp, '_';
        }
        $previous_slope=$slope;
        push @tmp, $slope;
    }
    
    my ($min, $max) = (0,0);
    $previous_slope = shift @tmp;
    my ($x,$W,$y) = (0,1,0);
    foreach my $slope (@tmp)
    {
        if ($previous_slope eq '_')
        {
            if ($slope eq '\\') { $y++; }
        }
        elsif ($previous_slope eq '\\')
        {
            if ($slope eq '\\') { $y++; }
        }
        elsif ($previous_slope eq '/')
        {
            if (($slope eq '_') or ($slope eq '/')) { $y--; }
        }
        if ($y < $min) { $min = $y; } elsif ($y > $max) { $max = $y; }
        $previous_slope = $slope;
        $W++;
    }
    unshift @tmp, '_';
    my $H = 1+$max - $min;
    
    my @map;
    foreach my $y (0..$H-1) { foreach my $x (0..$W-1){$map[$y][$x]='.'; }}
    ($x,$y) = (0,0);
    $previous_slope = '';
    $map[-$min][0] = $previous_slope= shift @tmp;
    foreach my $slope (@tmp)
    {
        if ($previous_slope eq '_')
        {
            if ($slope eq '\\') { $y++; }
        }
        elsif ($previous_slope eq '\\')
        {
            if ($slope eq '\\') { $y++; }
        }
        elsif ($previous_slope eq '/')
        {
            if (($slope eq '_') or ($slope eq '/')) { $y--; }
        }
        $previous_slope = $slope;
        $x++;
        $map[$y-$min][$x]=$slope;
    }
    return ($H, $W, @map);
}

sub printMap
{
    my ($inertia, $H, $W, @map) = @_;

    print "$inertia\n";
    print "$W $H\n";

    foreach my $y (0..$H-1) {
        foreach my $x (0..$W-1){
            print $map[$y][$x];
        }
        print "\n";
    }
}

sub makeRollerCoaster ()
{
    my ($length) = @_;
    
    my @slopes = qw/_ \ \//;
    my @roller_coaster;
    
    push @roller_coaster, '_';
    
    my $inertia = int($length /4);
    foreach my $i (1..$length-1)
    {
        my $slope = $slopes[int(rand(1+$#slopes))];
        push @roller_coaster, $slope;
    }
    push @roller_coaster, '_';
    
    return $inertia, @roller_coaster;
}


