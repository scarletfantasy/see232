
import com.sun.org.apache.bcel.internal.generic.NEW;

import java.util.*;
import java.io.*;
public class Main {


    static  Map<String,Vector<Character>> wordmap=new HashMap<String, Vector<Character>>();
    public static void main(String[] args) {
        try
        {
            int order=(int)System.in.read()-48;
            readfile("abc",order);

        /*for(Character c:word)
        {
            System.out.print(c);
        }*/
        randowriter(order);
        System.out.println(wordmap.size());
        }
        catch (Exception e)
        {

        }
    }


    public static void readfile(String bookname,int order)
    {



        try
        {
            InputStream fin = new FileInputStream("D:/idea/TomSawyer.txt");
            int i=0;
            String tmp="";
            while((i=fin.read())!=-1)
            {
                Character c= new Character((char) i);
                if(tmp.length()<order)
                {
                    tmp=tmp+c;
                }
                else
                {
                    if (wordmap.containsKey(tmp))
                    {
                        Vector<Character> tmpv=wordmap.get(tmp);
                        tmpv.add(c);
                        wordmap.put(tmp,tmpv);

                    }
                    else
                    {
                        Vector<Character> tmpv=new Vector<Character>();
                        tmpv.add(c);
                        wordmap.put(tmp,tmpv);
                    }
                    tmp=tmp.substring(1)+c;
                }



            }


        }
        catch (IOException e) {
            System.out.print("Exception");
        }

    }

    public  static  void randowriter(int order)
    {
        Random rand=new Random();
        int count=0;
        String now="",max="";
        for(String tmp:wordmap.keySet())
        {
           if(wordmap.get(tmp).size()>count)
            {
                max=tmp;
                count=wordmap.get(tmp).size();
            }
        }
        now=max;
        System.out.print(now);
        for(int i=0;i<1000;++i)
        {

            if(wordmap.containsKey(now))
            {
                count=(int)(rand.nextDouble()*(wordmap.get(now).size()));
                Character tmpc=wordmap.get(now).elementAt(count);
                System.out.print(tmpc);
                now=now.substring(1)+tmpc;

            }
            else
            {
                now=max;
                System.out.print(now);
            }
        }

    }
}
