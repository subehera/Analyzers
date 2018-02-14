#!/bin/bash

IN_DIR="/afs/cern.ch/user/m/mguilbau/AnalyzerForWei/CMSSW_8_0_24/src"
MACRO_DIR="Analyzers/Cumulants/macro"
INCLUDE_DIR="Analyzers/Cumulants/interface"
OUT_DIR="/eos/cms/store/user/mguilbau/cumulant/error120218_subjack"

HM=$1
multmin=$2
multmax=$3
subevt=$4
trg=$5
harm0=$6
harm1=$7
folder=$8
if test -z "$HM"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$multmin"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$multmax"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$subevt"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$trg"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$harm0"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$harm1"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi
if test -z "$folder"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
  echo "  - 6th argument: 1st harmonic [harm0]"
  echo "  - 7th argument: 2nd harmonic [harm1]"
  echo "  - 8th argument: folder name [folder]"
 exit 123;
fi

echo "Content of working dir folder: "
echo $IN_DIR
ls $IN_DIR
cd $IN_DIR
eval `scramv1 runtime -sh`

tdir=`mktemp -d`
echo $tdir
cd $tdir
mkdir macro
cp -r ${IN_DIR}/${MACRO_DIR}/* macro/.
mkdir interface
cp -r ${IN_DIR}/${INCLUDE_DIR}/* interface/.
cd macro
make clean
make
cd $tdir

echo "Content of tmp dir folder: "
echo $tdir
ls $tdir

fname="sc${harm0}${harm1}_vnm_PD${HM}_HM${trg}_${multmin}_${multmax}_nsub${subevt}.root"
if [ ${subevt} -eq 1 ] 
then
  macro/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu18/PAHighMultiplicity*/*${trg}*std_sc_v1/*/*/*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output "/eos/cms/store/user/mguilbau/cumulant/error120218_subjack/${fname}" --harmonicorder0 ${harm0} --harmonicorder1 ${harm1} --folder ${folder} --cumumaxorder 4 --jacksub
elif [ ${subevt} -eq 2 ]
then
  macro/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu18/PAHighMultiplicity*/*${trg}*${subevt}sub_sc_v1/*/*/*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output "/eos/cms/store/user/mguilbau/cumulant/error120218_subjack/${fname}" --harmonicorder0 ${harm0} --harmonicorder1 ${harm1} --folder ${folder} --cumumaxorder 4 --jacksub
elif [ ${subevt} -eq 3 ]
then
  macro/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu/PAHighMultiplicity*/*${trg}*_${subevt}sub_v11/*/*/*sc*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output "/eos/cms/store/user/mguilbau/cumulant/error120218_subjack/${fname}" --harmonicorder0 ${harm0} --harmonicorder1 ${harm1} --folder ${folder} --cumumaxorder 4 --jacksub
elif [ ${subevt} -eq 4 ]
then
  macro/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu18/PAHighMultiplicity*/*${trg}*${subevt}sub_sc_v1/*/*/*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output "/eos/cms/store/user/mguilbau/cumulant/error120218_subjack/${fname}" --harmonicorder0 ${harm0} --harmonicorder1 ${harm1} --folder ${folder} --cumumaxorder 4 --jacksub
else
 echo "wrong subevent number"
fi
mv $tdir/${fname} ${OUT_DIR}/.

cd $IN_DIR
rm -rf $tdir
