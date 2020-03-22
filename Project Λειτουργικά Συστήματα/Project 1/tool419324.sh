#!/bin/bash
filename=
idno=0
since=0
until='2019-12-30'
idnoedit=0
column=0
value=0
socialflag=0
firstflag=0
lastflag=0
since_date=0
until_date=$(date -d $until +"%Y%m%d")

#Τα παραπανω ειναι flags για το τι μας δινεται στην κληση του script, το flag until ειναιαρχικοποιημενο στο μεγιστο δυνατο. 

if [[ $# -eq 0 ]] ; then 
    echo '1054324-1054419'
    exit 0
fi

#Αν κληθει το script χωρις παραμετρους εκτυπωνει τα ΑΜ μας

while [ "$1" != "" ]; do
#οσο το πρωτο πεδιο δεν ειναι κενο
    case $1 in
	# αναλογως με το τι ειναι κανε shift τα πεδια και ενεργοποιησε το αναλογο flag, σε περιπτωση ημερομηνιας γινεται μετατροπη σε ακεραιο
-f)          
	 shift
         filename=$1
         ;;
-id)
	shift
	idno=$1
        ;;
--firstnames)   
	firstflag=1
	 ;;
--lastnames)
	lastflag=1
	;;
--born-since)
	shift
	since=$1
	since_date=$(date -d $since +"%Y%m%d")
	;;
--born-until)
	shift
        until=$1
	until_date=$(date -d $until +"%Y%m%d")
    ;;
--socialmedia)
	socialflag=1
	;;
--edit)
	shift
	idnoedit=$1
	shift
        column=$1
	shift
        value=$1
	;;
*)
	echo "Invalid parameter"
	#αν δωθει κατι περα απο τα επιθυμητα εκτυπωσε λαθος παραμετροι και βγες
	exit 1 
    esac
    shift
done

if [ -n "$filename" ];  then
#αν το ονομα αρχειου δεν ειναι κενο 
	if [ -e "$filename" ];  then
	#αν το ονομα αρχειου υπαρχει ως αρχειο
		if [ "$idno" != "0" ] ; then
		awk -v idno="$idno" 'BEGIN { FS = "|" }; !/#/ {if($1 == idno ) print $3,$2,$5}'  $filename
		#αν το flag του id δεν ειναι 0 ψαξε το id που δοθηκε και εκτυπωσε τις στηλες 3,2,5 αγνοωντας τις στηλες που ξεκινουν με #
		else
			if [ "$firstflag" -eq "1" ] ; then
		        awk 'BEGIN { FS = "|" } ;!/#/ {if(!seen[$3]++) print $3|"sort -u"}' $filename
				#αν ειναι ενεργοποιημενο το flag των firstnames εκτυπωνει ολα τα ονοματα ταξινομημενα αγνοωντας τις στηλες που ξεκινουν με #
			else
				if [ "$lastflag" -eq "1" ] ; then
                               	awk 'BEGIN { FS = "|" } ;!/#/ {if(!seen[$2]++) print $2|"sort -u"}' $filename
								#αν ειναι ενεργοποιημενο το flag των lastnames εκτυπωνει ολα τα επωνυμα ταξινομημενα αγνοωντας τις στηλες που ξεκινουν με #
                        	else
					if [ "$until_date" -ne "20191230" ] || [ "$since_date" -ne "0" ]; then
					awk -F '|' -v until="$until" -v since="$since" '!/#/ {if ((until >=$5) && (since <= $5)){ print } }' $filename
					#αν το until flag δεν ειναι ισο με το αρχικοποιημενο η το since flag διαφορετικο του 0 τοτε εκτυπωνει τις ημερομηνιες αναμεσα στα flags
					else 
						if  [ "$socialflag" -eq "1" ] ; then
						awk 'BEGIN { FS = "|" } ;!/#/ {A[$9]++}END {for(i in A) print i," "A[i]|"sort -u"}' $filename | tr -cd "[:print:]\n"
						#αν το flag για τα socialmedia ειναι ενργοποιημενο τοτε τα εκτυπωνει και αθροιζει τα ιδια πεδια εκτυπωνοντας τον αριθμο τους
						else 
							if [ "$column" -gt "1" ] && [ "$column" -lt "9" ] ; then
							echo "Overwriting the file."
                                                        awk -v idnoedit="$idnoedit" -v column="$column" -v value="$value" 'BEGIN {OFS =  FS = "|" };!/#/ {if($1 == idnoedit) $column=value}1' $filename > test.dat_tmp &&  mv test.dat_tmp $filename
							echo "File has been editted successfully."
							#αν τα flags ειναι καταλληλα εκτυπωνει το αρχειο με τις αλλαγες σε ενα προσωρινο και μετα το αποθηκευει πανω στο παλιο.
							
							else
							awk '!/#/ {print}' $filename
							#αν καμια αλλη συνθηκη δεν ισχυει εκτυπωνεται ολο το αρχειο αγνοωντας τα πεδια με #
							fi
						fi
					fi	
				fi
			fi			
		fi
	else
		echo "That file does not exist."
	fi
else
        echo "You didn't enter a file name"
	exit
fi
 
 



