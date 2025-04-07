# Description: This script checks for syntax errors in a shell script.

# variables
BACKTICK=$(grep -o '`' $1 | wc -l)
CASE=$(grep -Eo 'case .+ in' $1 | wc -l)
ESAC=$(grep -o 'esac' $1 | wc -l)
IF=$(grep -o ' if ' $1 | wc -l)
THEN=$(grep -Eo '([[:space:]]+| {2,})then' $1 | wc -l)
FI=$(grep -Eo '([[:space:]]+| {2,})fi' $1 | wc -l)
FOR=$(grep -o 'for ' $1 | wc -l)
DO=$(grep -x 'do' $1 | wc -l)
DONE=$(grep -x 'done' $1 | wc -l)

# display informations
echo "The script $1 contains:"
echo "Backticks: $BACKTICK"
echo "Case: $CASE"
echo "Esac: $ESAC"
echo "If: $IF"
echo "Then: $THEN"
echo "Fi: $FI"
echo "For: $FOR"
echo "Do: $DO"
echo "Done: $DONE"
echo "----------------------------------------"