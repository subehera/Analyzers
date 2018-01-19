#!/bin/bash

IN_DIR="/afs/cern.ch/user/m/mguilbau/AnalyzerForWei/CMSSW_8_0_24/src"
MACRO_DIR="Analyzers/Cumulants/macro"
OUT_DIR="/eos/cms/store/user/mguilbau/cumulant"

HM=$1
multmin=$2
multmax=$3
subevt=$4
trg=$5
if test -z "$HM"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
 exit 123;
fi
if test -z "$multmin"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
 exit 123;
fi
if test -z "$multmax"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
 exit 123;
fi
if test -z "$subevt"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
 exit 123;
fi
if test -z "$trg"; then
  echo "Usage as: "
  echo "  - 1st argument: HM HLT PATH number [HM]"
  echo "  - 2nd argument: minimum multiplicity [multmin]"
  echo "  - 3rd argument: maximum multiplicity [multmax]"
  echo "  - 4th argument: number of sub events [subevt]"
  echo "  - 5th argument: trigger path [trg]"
 exit 123;
fi

echo "Content of working dir folder: "
echo $IN_DIR
ls $IN_DIR
cd $IN_DIR
eval `scramv1 runtime -sh`

tdir=`mktemp -d`
cd $tdir
cp -r ${IN_DIR}/* .
cd ${MACRO_DIR}
make clean
make
cd $tdir

echo "Content of tmp dir folder: "
echo $tdir
ls $tdir

fname="cnm_vnm_HM_${multmin}_${multmax}_nsub${subevt}.root"
if [ $subevt -eq 1 ]
then
#${MACRO_DIR}/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu/PAHighMultiplicity${HM}/RecoSkim2016_*${trg}_*_std_*/*/*/*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output ${fname} 
${MACRO_DIR}/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu18/PA*/*c2_v1/*/*/*std*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output ${fname} 
else
#${MACRO_DIR}/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu/PAHighMultiplicity${HM}/RecoSkim2016_*${trg}_*_${subevt}sub_*/*/*/*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output ${fname} 
${MACRO_DIR}/PlotVnm --input "/eos/cms/store/group/phys_heavyions/flowcorr/SubCumu18/PA*/*c2_v1/*/*/*${subevt}sub*.root" --noffmin ${multmin} --noffmax ${multmax} --subevt ${subevt} --output ${fname} 
fi

mv $tdir/${fname} ${OUT_DIR}/.

cd $IN_DIR
rm -rf $tdir
