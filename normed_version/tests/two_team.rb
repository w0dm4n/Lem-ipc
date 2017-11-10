a = 0
for i in 1..50 do
	

	if a == 0
		pid = Process.fork do
			s = "./lemipc 1";
			system(s);
		end
		a = 1;
	else
		pid = Process.fork do
			s = "./lemipc 2";
			system(s);
		end
		a = 0;
	end
	#sleep(0.5);
end
