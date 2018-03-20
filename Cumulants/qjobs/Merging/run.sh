#!/bin/bash

IN_DIR="/afs/cern.ch/user/m/mguilbau/AnalyzerForWei/CMSSW_8_0_24/src"
MACRO_DIR="Analyzers/Cumulants/macro"
DATA_DIR="/eos/cms/store/group/phys_heavyions/flowcorr/SubCumuNew"
OUT_DIR="/eos/cms/store/group/phys_heavyions/flowcorr/SubCumuNew/MergeFiles"

nsub=${1}
version=${2}
system=${3}
PD=${4}
trg=${5}


if test -z "$nsub"; then
  echo "Missing nsub parameter. Usage as: "
  echo "  - 1st argument: nsub = ${nsub}"
  echo "  - 2nd argument: version = v${version}"
  echo "  - 3rd argument: system = ${system}"
  echo "  - 4th argument: PD = ${PD}"
  echo "  - 5th argument: trigger path = ${trg}"
 exit 123;
fi
if test -z "$version"; then
  echo "Missing version parameter. Usage as: "
  echo "  - 1st argument: nsub = ${nsub}"
  echo "  - 2nd argument: version = v${version}"
  echo "  - 3rd argument: system = ${system}"
  echo "  - 4th argument: PD = ${PD}"
  echo "  - 5th argument: trigger path = ${trg}"
 exit 123;
fi
if test -z "$system"; then
  echo "Missing system parameter. Usage as: "
  echo "  - 1st argument: nsub = ${nsub}"
  echo "  - 2nd argument: version = v${version}"
  echo "  - 3rd argument: system = ${system}"
  echo "  - 4th argument: PD = ${PD}"
  echo "  - 5th argument: trigger path = ${trg}"
 exit 123;
fi
if test -z "$PD"; then
  echo "Missing PD parameter. Usage as: "
  echo "  - 1st argument: nsub = ${nsub}"
  echo "  - 2nd argument: version = v${version}"
  echo "  - 3rd argument: system = ${system}"
  echo "  - 4th argument: PD = ${PD}"
  echo "  - 5th argument: trigger path = ${trg}"
 exit 123;
fi
if test -z "$trg"; then
  echo "WARNNING::Missing trg parameter. Usage as: "
  echo "  - 1st argument: nsub = ${nsub}"
  echo "  - 2nd argument: version = v${version}"
  echo "  - 3rd argument: system = ${system}"
  echo "  - 4th argument: PD = ${PD}"
  echo "  - 5th argument: trigger path = ${trg}"
fi

echo "Content of working dir folder: "
echo $IN_DIR
ls $IN_DIR
cd $IN_DIR
eval `scramv1 runtime -sh`

cd $OUT_DIR
mkdir "${PD}_${nsub}_v${version}"
OUT_MERGED=$OUT_DIR/${PD}_${nsub}_v${version}

tdir=`mktemp -d`
echo $tdir
cd $tdir


#####
##### Sub merging in group of 10 ####
#####

iter=0
nmerge=0
j=""

if test -z "$trg"; then
   ls ${DATA_DIR}/${PD}/*${trg}*${nsub}*_v${version}/*/*/*.root >> processedfiles_${PD}_MB_${nsub}_v${version}.txt
else
   ls ${DATA_DIR}/${PD}/*${trg}*${nsub}*_v${version}/*/*/*.root >> processedfiles_${PD}_${trg}_${nsub}_v${version}.txt
fi

for i in `ls ${DATA_DIR}/${PD}/*${trg}*${nsub}*_v${version}/*/*/*.root`
do
   j="$j $i"
   iter=$((iter+1))

   if [ $iter -gt 10 ]; then
      outfilesub="cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_submerging${nmerge}.root"
      if test -z "$trg"; then
         outfilesub="cumulant_${system}_${PD}_MB_${nsub}_v${version}_submerging${nmerge}.root"
      fi

      echo "hadd -O ${outfilesub}$j"
      hadd -O ${outfilesub}$j
      mv  ${outfilesub} ${OUT_MERGED}
      echo ""
      iter=0
      nmerge=$((nmerge+1))
      j=""
   fi
done

outfilesub="cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_submerging${nmerge}.root"
if test -z "$trg"; then
   outfilesub="cumulant_${system}_${PD}_MB_${nsub}_v${version}_submerging${nmerge}.root"
fi

echo "hadd -O ${outfilesub}$j"
hadd -O ${outfilesub}$j 
mv  ${outfilesub} ${OUT_MERGED}

echo ""


#####
##### Macro merging in group of 10 ####
#####

iter=0
nmerge=0
j=""

for i in `ls ${OUT_MERGED}/cumulant_${system}_${PD}*_${nsub}_v${version}_submerging*.root`
do
   j="$j $i"
   iter=$((iter+1))

   if [ $iter -gt 10 ]; then
      outfilemacro="cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_macromerging${nmerge}.root"
      if test -z "$trg"; then
         outfilemacro="cumulant_${system}_${PD}_MB_${nsub}_v${version}_macromerging${nmerge}.root"
      fi

      echo "hadd -O ${outfilemacro}$j"
      hadd -O ${outfilemacro}$j
      mv  ${outfilemacro} ${OUT_MERGED}
      echo ""
      iter=0
      nmerge=$((nmerge+1))
      j=""
   fi
done

outfilemacro="cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_macromerging${nmerge}.root"
if test -z "$trg"; then
   outfilemacro="cumulant_${system}_${PD}_MB_${nsub}_v${version}_macromerging${nmerge}.root"
fi

echo "hadd -O ${outfilemacro}$j"
hadd -O ${outfilemacro}$j 
mv  ${outfilemacro} ${OUT_MERGED}

if test -z "$trg"; then
   rm ${OUT_MERGED}/cumulant_${system}_${PD}_MB_${nsub}_v${version}_submerging*.root
else
   rm ${OUT_MERGED}/cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_submerging*.root
fi

####
#### Final merging in group of 10 ####
####

outputfinal="cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_final.root"
if test -z "$trg"; then
   outputfinal="cumulant_${system}_${PD}_MB_${nsub}_v${version}_final.root"
fi

echo "hadd -O ${outputfinal} ${OUT_MERGED}/cumulant_${system}_${PD}*_${nsub}_v${version}_macromerging*.root" 
hadd -O ${outputfinal} ${OUT_MERGED}/cumulant_${system}_${PD}*_${nsub}_v${version}_macromerging*.root

echo "mv ${outputfinal} ${OUT_MERGED}" 
mv ${outputfinal} ${OUT_MERGED}
mv processedfiles_${PD}_*_${nsub}_v${version}.txt ${OUT_MERGED}

if test -z "$trg"; then
   rm ${OUT_MERGED}/cumulant_${system}_${PD}_MB_${nsub}_v${version}_macromerging*.root
else
   rm ${OUT_MERGED}/cumulant_${system}_${PD}_${trg}_${nsub}_v${version}_macromerging*.root
fi

echo "Content of tmp dir folder: "
echo $tdir
ls $tdir

cd $IN_DIR
rm -rf $tdir
