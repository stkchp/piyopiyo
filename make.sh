#!/bin/bash
#
# make piyopiyo binary
#   clang 3.9 / ninja 1.6
#
cd $(dirname $0)
CURDIR=$(pwd)
BUILDDIR=$CURDIR/build
CURFILE=$BUILDDIR/build.ninja
NEWFILE=$BUILDDIR/.build.ninja
EXECFILE=piyopiyo

[[ ! -d $BUILDDIR ]] && mkdir $BUILDDIR
cd $BUILDDIR

if [[ $# -eq 1 ]] && [[ $1 == "clean" ]]
then
	echo ""
	echo "== CLEAN =="
	echo ""
	[[ -f .build.ninja ]] && rm -v .build.ninja
	[[ -f build.ninja  ]] && rm -v build.ninja
	[[ -d obj          ]] && rm -rfv obj
	[[ -d release      ]] && rm -rfv release
fi

cat << '_EOL' > $NEWFILE
builddir = release
ninja_required_version = 1.6

cxxcompile_command = clang++
cxxcompile_flags = -std=c++14 -Wall -g3
link_command = clang++
archive_libs = -lpthread
static_libs = -lc++ -lc++abi
shared_libs = -lglfw -lGL -lrtaudio -lc -lm
link_flags = -v -std=c++14 -Wl,--as-needed -nodefaultlibs -Wl,--whole-archive $archive_libs -Wl,--no-whole-archive -Wl,-Bstatic $static_libs -Wl,-Bdynamic $shared_libs

# 
# rule
#
rule cxxcompile
  depfile = $out.d
  description = compile(c++) $in to $out
  command = $cxxcompile_command $flto -MMD -MF $out.d $cxxcompile_flags -c $in -o $out

rule link
  description = link $in to $out
  command = $link_command $in $flto $link_flags -o $out
_EOL

OBJS=""

while read line
do
	obj=$(echo $line | sed -e 's/\.\.\/src/obj/' | sed -e 's/\.cpp$/\.o/')
	OBJS="$obj $OBJS"
	echo "build $obj: cxxcompile $line" >> $NEWFILE
done < <(find ../src/ | grep '\.cpp$')

echo "build piyopiyo: link $OBJS" >> $NEWFILE
echo "default piyopiyo" >> $NEWFILE

diff $CURFILE $NEWFILE > /dev/null
[[ $? -ne 0 ]] && cp -f $NEWFILE $CURFILE


echo ""
echo "== BUILD =="
echo ""
ninja -v
[[ $? -ne 0 ]] && exit 1


echo ""
echo "== SHARED LIBRARY =="
echo ""
readelf -a piyopiyo | grep NEEDED


echo ""
echo "== VERSION TABLE =="
echo ""
objdump -T piyopiyo | egrep "^[0-9a-f]" | cut -c 50- | awk ' $2 != "" {print $1}' | sort | uniq -c

