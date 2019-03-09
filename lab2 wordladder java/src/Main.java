import java.util.*;
import java.io.*;
public class Main {

    public static void main(String[] args)
    {

        boolean i= check("bat","cat");
        readfile();
        Scanner reader=new Scanner(System.in);
        while (true)
        {
            System.out.print("do you want to exit");
            String command=reader.nextLine();
            if(command.equals("yes"))
            {
                break;
            }
            System.out.print("please input the begin word");
            String begin=reader.nextLine();
            System.out.print("please input the end word");
            String end=reader.nextLine();
            wordladder(begin,end);
        }


    }
    static Map<Integer,Vector<String>> wordmap=new HashMap<Integer,Vector<String>>();
    public static void readfile()
    {
        try
        {
            FileInputStream fin=new FileInputStream("D:\\ideaprogram\\lab2 wordladder\\EnglishWords.txt");
            String tmp;
            Scanner fscanner=new Scanner(fin);
            while(fscanner.hasNextLine())
            {
                tmp=fscanner.nextLine();
                int l=tmp.length();
                if(wordmap.containsKey(l))

                {
                    Vector<String> tmpv=wordmap.get(l);
                    tmpv.add(tmp);
                    wordmap.put(l,tmpv);
                }
                else
                {
                    Vector<String> tmpv=new Vector<String>();
                    tmpv.add(tmp);
                    wordmap.put(l,tmpv);
                }
            }
            System.out.println("read file success");
        }
        catch (Exception e)
        {

        }
    }
    public static void wordladder(String begin,String end)
    {

        try {
            LinkedList<LinkedList<String>> allladder=new LinkedList<LinkedList<String>>();
            LinkedList<String> ladder=new LinkedList<String>();
            Vector<String> allword=wordmap.get(begin.length());
            ladder.addLast(begin);
            allladder.addLast(ladder);
            int lcount=0;
            while (true)
            {
                ladder=allladder.getFirst();
                if(allladder.size()==0)
                {
                    System.out.print("not find");
                }
                allladder.removeFirst();
                String now=ladder.getLast();
                if(ladder.size()>lcount)
                {
                    ++lcount;
                }
                for (String tmps_allword:allword)
                {
                    if(check(tmps_allword,now))
                    {
                        if(tmps_allword.equals(end))
                        {
                            for (String tmps_ladder:ladder)
                            {
                                System.out.println(tmps_ladder);
                            }
                            System.out.println(end);
                            return;
                        }
                        boolean flag=false;
                        for (String tmps_ladder:ladder)
                        {
                            if(tmps_ladder.equals(tmps_allword))
                            {
                                flag=true;
                                break;
                            }
                        }
                        if(!flag)
                        {

                            LinkedList<String> cladder=new LinkedList<String>(ladder);
                            cladder.addLast(tmps_allword);
                            allladder.addLast(cladder);

                        }
                    }

                }
            }
        }
        catch (Exception e)
        {

        }



    }
    public static Boolean check(String a,String b)
    {
        int l=a.length();
        int count=0;
        for(int i=0;i<l;++i)
        {
            String tmpa=a.substring(i,i+1);
            String tmpb=b.substring(i,i+1);
            if(!tmpa.equals(tmpb))
            {
                ++count;
            }
        }
        if(count==1)
        {
            return true;
        }
        return false;

    }

}
