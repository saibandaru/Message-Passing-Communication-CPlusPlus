:run.bat

cd Sockets/Debug/ 


@echo OFF
@echo:

@echo:
echo Input is given in a .txt file that is read as a string
START Executive.exe 
START Server.exe localhost:9000 ../../TestDir/Server1/
START Server.exe localhost:9010 ../../TestDir/Server2/
START Client.exe localhost:8090 ../../TestDir/Client1/
START Client.exe localhost:8080 ../../TestDir/Client2/
@echo:

cd ../..