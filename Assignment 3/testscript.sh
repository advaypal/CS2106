make clean
make
makefs fs.cfg

echo "Testing overloading the system with huge files ..."
./checkin ../testcases/testvideo.mp4 password
echo "############# Test completed! ################"

echo "Testing checkin non-existence file..."
./checkin non-existence.txt password | grep "The file non-existence.txt was unable to be checked in: No such file or directory" &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi
echo "############# Test completed! ################"

echo "Testing checkout non-existence file..."
./checkout non-existence.txt password | grep "FILE NOT FOUND" &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi

echo "############# Test completed! ################"

echo "Testing file from other directory..."

echo "############# Testing diarhack.txt ###############"
./checkin ../testcases/diaryhack.txt password
./checkout diaryhack.txt password
diff -wi diaryhack.txt ../testcases/diaryhack.txt 2> /dev/null
    if [ $? -ne 0 ]
        then
          echo -e "\t Failed test case."
          
        else
          echo -e "\t Passed test case."
    fi
rm diaryhack.txt
./delfile diaryhack.txt
echo "############# Test completed! ################"

echo "############### Testing test.txt ################"
./checkin ../testcases/test.txt password
./checkout test.txt password
diff -wi test.txt ../testcases/test.txt 2> /dev/null
   if [ $? -ne 0 ]
        then
          echo -e "\t Failed test case."
          
        else
          echo -e "\t Passed test case."
    fi
rm test.txt
./delfile test.txt
echo "############# Test completed! ################"

echo "############## Testing adventur.txt ################"
./checkin ../testcases/adventur.txt password
./checkout adventur.txt password
diff -wi adventur.txt ../testcases/adventur.txt 2> /dev/null
	 if [ $? -ne 0 ]
        then
          echo -e "\t Failed test case."
          
        else
          echo -e "\t Passed test case."
    fi
rm adventur.txt
./delfile adventur.txt
echo "############# Test completed! ################"

echo "################ Testing from same directory ############"

echo "############# Testing diarhack.txt ###############"
cp ../testcases/diaryhack.txt diaryhack.txt
./checkin diaryhack.txt password
rm diaryhack.txt
./checkout diaryhack.txt password
diff -wi diaryhack.txt ../testcases/diaryhack.txt 2> /dev/null
    if [ $? -ne 0 ]
        then
          echo -e "\t Failed test case."
          
        else
          echo -e "\t Passed test case."
    fi
./delfile diaryhack.txt
rm diaryhack.txt
echo "############# Test completed! ################"

echo "############### Testing test.txt ################"
cp ../testcases/test.txt test.txt
./checkin test.txt password
rm test.txt
./checkout test.txt password
diff -wi test.txt ../testcases/test.txt 2> /dev/null
   if [ $? -ne 0 ]
        then
          echo -e "\t Failed test case."
          
        else
          echo -e "\t Passed test case."
    fi
./delfile test.txt
rm test.txt
echo "############# Test completed! ################"

echo "############## Testing adventur.txt ################"
cp ../testcases/adventur.txt adventur.txt
./checkin adventur.txt password
rm adventur.txt
./checkout adventur.txt password
diff -wi adventur.txt ../testcases/adventur.txt 2> /dev/null
	 if [ $? -ne 0 ]
        then
          echo -e "\t Failed test case."
          
        else
          echo -e "\t Passed test case."
    fi
./delfile adventur.txt   
rm adventur.txt
echo "############# Test completed! ################"

echo "############## Testing checking out with incorrect password! ################"
./checkin ../testcases/test.txt password
./checkout test.txt wrongpassword
diff test.txt ../testcases/test.txt >temp.txt 2>&1
	if [ $? != 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
	fi
rm temp.txt		
./delfile test.txt
echo "############# Test completed! ################"

echo "############# Testing deleting file ##########################"
echo "############# Inserting test.txt ... ###################"
./checkin ../testcases/test.txt password
./delfile test.txt
echo "############# Inserting diaryhack.txt ... ###################"
./checkin ../testcases/diaryhack.txt password
./delfile diaryhack.txt
echo "############# Inserting adventur.txt ... ###################"
./checkin ../testcases/adventur.txt password
./delfile adventur.txt

echo "############# Test completed! ################"

echo "################ Testing setting & getting attribute #################### "
./checkin ../testcases/test.txt password
./checkin ../testcases/diaryhack.txt password
./checkin ../testcases/adventur.txt password
echo "Setting test.txt with invalid attribute"
./attrfile test.txt invalid | grep "Invalid Attribute provided." &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi

echo "Setting diarhack.txt with invalid attribute"
./attrfile diaryhack.txt invalid | grep "Invalid Attribute provided." &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
			./getattr diaryhack.txt
	fi

echo "Setting adventur.txt with invalid attribute"
./attrfile adventur.txt invalid | grep "Invalid Attribute provided." &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
			./getattr adventur.txt
	fi


echo "Setting test.txt with W..."
./attrfile test.txt W | grep "Setting attribute to be Read & Write." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr test.txt | grep "test.txt's attribute is W!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi

echo "Setting diarhack.txt with W..."
./attrfile diaryhack.txt W | grep "Setting attribute to be Read & Write." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr diaryhack.txt | grep "diaryhack.txt's attribute is W!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr diaryhack.txt
	fi
echo "Setting adventur.txt with W..."
./attrfile adventur.txt W | grep "Setting attribute to be Read & Write." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr adventur.txt | grep "adventur.txt's attribute is W!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr adventur.txt
	fi
echo "Setting test.txt with w..."
./attrfile test.txt w | grep "Setting attribute to be Read & Write." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr test.txt | grep "test.txt's attribute is W!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi
echo "Setting diaryhack.txt with w..."
./attrfile diaryhack.txt w | grep "Setting attribute to be Read & Write." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr diaryhack.txt | grep "diaryhack.txt's attribute is W!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr diaryhack.txt
	fi
echo "Setting adventur.txt with w..."
./attrfile adventur.txt w | grep "Setting attribute to be Read & Write." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr adventur.txt | grep "adventur.txt's attribute is W!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr adventur.txt
	fi
echo "Setting test.txt with R..."
./attrfile test.txt R | grep "Setting attribute to be Read Only." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr test.txt | grep "test.txt's attribute is R!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi
echo "Setting diarhack.txt with R..."
./attrfile diaryhack.txt R | grep "Setting attribute to be Read Only." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr diaryhack.txt | grep "diaryhack.txt's attribute is R!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr diaryhack.txt
	fi
echo "Setting adventur.txt with R..."
./attrfile adventur.txt R | grep "Setting attribute to be Read Only." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr adventur.txt | grep "adventur.txt's attribute is R!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr adventur.txt
	fi
echo "Setting test.txt with r..."
./attrfile test.txt r | grep "Setting attribute to be Read Only." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr test.txt | grep "test.txt's attribute is R!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr test.txt
	fi
echo "Setting diarhack.txt with r..."
./attrfile diaryhack.txt r | grep "Setting attribute to be Read Only." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr diaryhack.txt | grep "diaryhack.txt's attribute is R!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr diaryhack.txt
	fi
echo "Setting adventur.txt with r..."
./attrfile adventur.txt r | grep "Setting attribute to be Read Only." &> /dev/null
	if [ $? == 0 ]
		then
			./getattr diaryhack.txt | grep "diaryhack.txt's attribute is R!" &> /dev/null
				if [ $? == 0 ]
					then
						echo -e "\t Passed test case."
				else 
					echo -e "\t Failed test case."
			fi
		else 
			echo -e "\t Failed test case."
			./getattr diaryhack.txt
	fi

echo "############# Test completed! ################"


echo "################ Testing deleting file with R attribute #################### "
echo "############# Deleting test.txt ... ###################"
./delfile test.txt | grep "Read-only file : Unable to delete!" &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
	fi
echo "############# Deleting diaryhack.txt ... ###################"
./delfile diaryhack.txt | grep "Read-only file : Unable to delete!" &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
	fi
echo "############# Deleting adventur.txt ... ###################"
./delfile adventur.txt | grep "Read-only file : Unable to delete!" &> /dev/null
	if [ $? == 0 ]
		then
			echo -e "\t Passed test case."
		else 
			echo -e "\t Failed test case."
	fi

make clean




