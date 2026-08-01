# A script that chooses a directory, and runs the tests in the directory. Educational.
# The first argument is the name of the directory.
# The second argument is the text file where the results are stored.

function run_test {
    for file in $1/*.cpp; do 
        echo $file
    done 
}

if [[ $# -ne 2 ]]; then
    exit 42
fi

echo $# $1 $2

directory=$1
filename=$2
run_test $directory