# usage: bash run.sh -c output.json -m map_dir [-t tmp_dir] [-b]
# -b means whether run build.sh first
# egs:  bash run.sh -c output.json -m ../data/map/question_3_map -t hesy_tmp -b
# use abosolute path


WITHBUILD="no"
TMPDIRPATH="tmp"
while getopts "t:bm:c:" option; do
   case $option in
      t) TMPDIRPATH=$OPTARG
        ;;
      b) WITHBUILD="build"
        ;;
      m) INPUT_MAP_DIR_PATH=$OPTARG
        ;;
      c) OUTPUT_COMMAND_PATH=$OPTARG
        ;;
      \?) echo "Error: Invalid option"
         exit;;
   esac
done

if [ ! -d $TMPDIRPATH ]; then
  mkdir $TMPDIRPATH
fi

rm -rf $TMPDIRPATH/*

if  [[ $WITHBUILD = "build" ]]; then
    bash build.sh || exit 1
fi

for map_path in `find $INPUT_MAP_DIR_PATH  -path "*.json"| sort`
do
    ./main $map_path $TMPDIRPATH/$(basename $map_path) || exit 1
done

find $TMPDIRPATH -path "*.json"|sort |python concat_output_json.py -o $OUTPUT_COMMAND_PATH

