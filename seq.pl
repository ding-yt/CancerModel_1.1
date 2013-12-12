#!/usr/bin/perl
use Math::Random qw(:all);

$input = $ARGV[0];
$output = $ARGV[1];
$nex;

$dirname = "/Users/dyt/Dropbox/cancerEvolution/script/CancerModel_1_data/simulation";
@filelist;
@samplelist;
$sample_size;
%mutation_list;
$sample_begin = 0;
$primary_begin = 1;
$mutate_position = 0;
$migration = 1;
%cell_type;
@mu = (0.03, 0.06, 0.12, 0.24, 0.5, 0.75, 1);

opendir (DIR1, $dirname) || die " can't open $dirname!\n ";
@filelist = readdir DIR1;
closedir DIR1;
shift @filelist;
shift @filelist;

foreach (@filelist) {
    $filename = $dirname."/".$_;
    $output = $dirname."/"."seq_".$_;
    $nex = $dirname."/".$_;
    $treefile_name = "/home/biodept/yd44/cancerEvo/simulation/tree/".$_.".tre";
    
    open (FILE1, $filename) or die "can't open $_\n";
    print ("file is: $_\n");
    
    while (<FILE1>){
        chomp;
        my $templine = $_;
        if($templine =~ /No.+migration/i){
            print ("find no migration\n");
            $migration = 0;
        }
        if ($sample_begin == 0){
            #            print ("$templine\n");
            if ($templine =~ /sample.+size:\s+(\d+)/i){
                $sample_size = $1;
                $sample_begin = 1;
            }elsif($primary == 1){
                $templine =~ /^(\d+)\s+(\d+)/;
                $cell_type{$1} = $2;
            }elsif($templine =~ /Secondary/i){
                $primary = 0;
            }else{
                next;
            }
        }else{
            if ( $templine =~ /\d+\s+\d+\s+/){
                my @temp = split (/\s+/, $templine);
                push @samplelist, \@temp;
                #                foreach (@temp){print ("$_\t");}
                #                print ("\n");
            }
        }
    }
    close FILE1;
    
    
    if ($sample_begin == 1){
    foreach (@samplelist) {
        @sample_parents = @{$_};
#        print ("$#sample_parents+1\n");
        for ($i = $#sample_parents; $i>=0; $i--){
            if (! exists $mutation_list{$sample_parents[$i]}){
                #    print ("no $sample_parents[$i] found\n" );
                
                #### Find out cell type #####
                if ($sample_parents[$i] == -1 ){
                    $mu = $mu[0];
                    @{$mutation_list{-1}} = (0);
                }elsif ($sample_parents[$i] == -2){
                    $mu = $mu[1];
                    @{$mutation_list{-2}} = (0);
                }else{
                    $mu = $mu[$cell_type{$sample_parents[$i]}];
          
                
                #### Decide mutation ~ possion #####
                    $m_number = random_poisson(1,$mu);
#                                print ("$mu\t$m_number\n");
                    if ( $m_number != 0){
                        for ( $j=1; $j<=$m_number; $j++){
                            $mutate_position ++;
                            push @{$mutation_list{$sample_parents[$i]}}, $mutate_position;
                        }
                    }else{
                        push @{$mutation_list{$sample_parents[$i]}},0;
                    }
                }
            }
            
        }
        #       print ("$#{$_}+1\n");
    }
#    print ("samplelist has size of $#samplelist +1\n");
#    foreach (sort keys %mutation_list){
#        print ("$_ => ");
#        foreach (@{$mutation_list{$_}}){
#            print ("$_\t");
#        }
#        print ("\n");
#    }
    
#    open (FILE1, $filename) or die "can't open $_\n";
    

    
    foreach (@samplelist) {
        @sample_parents = @{$_};
        $index = 0;
#        print ("$#samplelist\t$#sample_parents\n");
        $seq_name = "c".$sample_parents[0]."_t".$cell_type{$sample_parents[0]};
        if ($sample_parents[$#sample_parents] == -1){
            @sequence = ("A") x ($mutate_position+5);
        }else{
            @sequence = ("A") x ($mutate_position+5);
            for ($i=0; $i< ($#sequence+1)/10;$i++){
                $sequence[$i] = "C";
            }
        }
#        @sequence = ("A") x 30000001;
#        push @sequence, "A";
        foreach (@sample_parents){
            $parents = $_;
            foreach (@{$mutation_list{$parents}}){
                $sequence[$_] = "T";
            }
        }
        shift @sequence;
        $seq{$seq_name} = join ("", @sequence);
        
    }
    
        print ("max diff $mutate_position\n");
        
        if ($migration != 0){
            $output .="_m";
            $nex .= "_m";
        }
        
        ################# FASTA ######################
        open (OUTFILE, ">$output") or die " can't open $output\n";
        select OUTFILE;        
        foreach (sort keys %seq){
            print (">$_\n$seq{$_}\n");
        }
        close OUTFILE;
        select STDOUT;
        print ("output $output ready!\n");
        
        ################# NEX #####################
        $nex .=".nex";
        open (NEXFILE,">$nex") or die "can't open $nex\n";
        select NEXFILE;
        print "#NEXUS\n";
        print "Begin data;\n";
        print "\tDimensions ntax=$sample_size nchar=$mutate_position;\n";
#        print "\tDimensions ntax=$sample_size nchar=30000000;\n";
        print "\tFormat datatype=dna interleave=yes gap=-;\n";
        print "\tMatrix\n";
        foreach (sort keys %seq){
            print ("$_\t$seq{$_}\n");
        }
        print "\t;\nEnd;\n";
        print "Begin paup;\n";
#÷       print "Log file=$logfile replace=yes;";
        print "Dset distance=JC;\n";
        print "NJ brlens=yes replace=yes;\n";
        #print "RootTrees rootMethod=midpoint;\n";
#        print "Outgroup $root_rec;\n";
        #print "RootTrees;\n";
        print "savetrees file=$treefile_name brlens=yes root=yes replace=yes;\n";
        #print "savetrees file=$treefile_name brlens=yes replace=yes;\n";
        print "end;\n";
        print "quit;\n";
        close NEXFILE;
        select STDOUT;
        
    }
    undef %mutation_list;
    undef @samplelist;
    undef %seq;
    $mutate_position = 0;
    $sample_begin = 0;
    $primary = 1;
    $migration = 1;
   
}