msbuild tsp-greedy.sln && py generate.py < settings.in && .\x86\Debug\tsp-greedy.exe TSPInput.txt.txt > .\x86\Debug\path.out || .\x64\Debug\tsp-greedy.exe TSPInput.txt > .\x64\Debug\path.out && py visualize.py
