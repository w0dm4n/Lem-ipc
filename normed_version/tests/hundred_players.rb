for i in 1..100 do
	pid = Process.fork do
		r = rand(1...10);
		s = "./lemipc " + r.to_s;
		system(s);
	end
	#sleep(0.5);
end
