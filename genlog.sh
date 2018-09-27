#!/usr/bin/env bash
echo
echo "[syslog]"
echo "--------"
syslog_tmp_file=/tmp/prntdisk.tmp
syslog_file=./llsyslog
dd if=80m.img of=$syslog_tmp_file bs=1 count=32 skip=`echo "obase=10;ibase=16;1C88000" | bc` 2> /dev/null
dd if=80m.img of=$syslog_file bs=1 count=`head -n 1 $syslog_tmp_file | sed 's/\ //g'` skip=`echo "obase=10;ibase=16;1C88000" | bc` 2> /dev/null
echo >> $syslog_file
echo "time: "`cat $syslog_file | head -n 3 | tail -n 1`
echo
cat $syslog_file | sed '1,3d' > filedesc.dot
cat filedesc.dot | sudo bash ./splitgraphs.sh
sudo rm -f *.dot llsyslog
echo

exit 0