class Solution 
{
public:
	/*Example: [acbca,5],[abc,1]
    			acbca | acbca | acbca | acbca | acbca
				` ```     ```     ```     ```     `` 
		cir     	1		2		3		4		5
		rest		1		1		1		1		1
					start   stop
		res = (prefix + repetition pattern * repeat times) / n2
		prefix = cir[start]
		repetition pattern = (cir[stop]-cir[start]) / (stop-start)
		repeat times = n1-start 
    */
    int getMaxRepetitions(string s1, int n1, string s2, int n2) 
    {
    	vector<int> cir(102,-1);
    	vector<int> rest(102,-1);

    	int start=-1;
    	int stop=-1;
    	int pos=0;
    	int cirtimes=0;

    	cir[0]=rest[0]=0;
    	for(int i=1;i<=s2.size()+1;++i)
    	{
    		for(int j=0;j<s1.size();++j)
    			if(s2[pos]==s1[j])
    			{
    				++pos;
    				if(pos==s2.size()) ++cirtimes,pos=0;	
    			}
    		for(int k=0;k<i;++k) if(pos==rest[k]) {start=k,stop=i;break;}
    		cir[i]=cirtimes, rest[i]=pos;
    		if(start>=0) break;
    	}
    	if(stop>=n1) return (int)cir[n1]/n2;
    	return (int)(cir[start]+(cir[stop]-cir[start])/(double)(stop-start)*(n1-start))/n2;
    }
};