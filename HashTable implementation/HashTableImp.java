import java.util.Arrays;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;


/*********************************************
 * CO322: Data structures and algorithms
 * Implementation of the hashTable
 *********************************************/
class HashTableImp implements HashTable {

    /* Put your code here */
    static class Node { // linked list
        String key;
        int value;
        Node next;

        // Constructor
        Node(int d,String word)
        {
            key = word;
            value = d;
            next = null;
        }
    }
    Node table[];
    int buckets;
    public HashTableImp(int buckets) {
        // create a open hash table with given number of buckets
        this.buckets = buckets;
        table = new Node[buckets];
        Arrays.fill(table,null);
    }

    public void insert(String key){

     int bucketNumber = hashFunction1(key);

     if(table[bucketNumber] == null){ // create head of the linked list if no elements in the table[bucketNumber]
         Node new_node = new Node(1,key);
         new_node.next = null;
        table[bucketNumber] = new_node ;
     }else{ // if head is there then insert word to the linked list or if word is the increment the value
         Node current = table[bucketNumber];

         while(current != null){
             if(current.key.equalsIgnoreCase(key)){
                 current.value++;
                 break;
             }
             if(current.next == null){
                 Node new_node1 = new Node(1,key);
                 new_node1.next = null;
                 current.next = new_node1 ;
                 break;
             }
             current = current.next;

         }
     }

    }

    public int search(String key){ // search a given word
        int bucketNumber = hashFunction1(key);
        if(table[bucketNumber] == null){
            return 0;
        }else{
            Node current = table[bucketNumber];

            while (current != null){
                if(current.key.equalsIgnoreCase(key)){
                    return current.value ;
                }
                current = current.next;
            }
        }
        return 0;
    }

    public int hashFunction1(String key){ // hash function 1

        int bucketNumber = 0;
        int sum = 0;

       char ar[] = key.toCharArray();

       for(int i=0;i< ar.length ;i++){

           int num = ar[i];
           if(num < 91){
               num = num + 32 ;
           }
           sum = sum + (num* (i+1)); // multiply ascii value of lowercase character with its position in the word and add it to sum
       }
       bucketNumber = sum%buckets ; // take mod of sum by buckets

        return bucketNumber;
    }
    public void numberOfEnteries(){
        int sum=0;
        for(int i=0;i<buckets;i++){
            int count = 0;
            Node current = table[i];
            while(current != null){
                count++;
                current = current.next;
            }
            sum = sum + count;
            System.out.println(i+" "+count);
        }
       System.out.println(sum);
    }
    public int hashFunction2(String key){ // hash function 2
       int bucketNumber = 0;

        int sum = 0;
        char ar[] = key.toCharArray();
        for(int i=0;i< ar.length ;i++){

            int num = ar[i]; //
            if(num < 91){
                num = num + 32 ;
            }
            sum = (sum* 601 + num)%buckets; // add ascii value of lowercase character to a multiplication of large prime number and sum and take mod by buckets
        }
        bucketNumber = sum ;

        return bucketNumber;
    }

public static void main(String args[]) throws IOException{
HashTableImp h = new HashTableImp(200);

    File f1=new File("src/sample-text2.txt"); //Creation of File Descriptor for input file
    String[] words=null;  //Intialize the word Array
    FileReader fr = new FileReader(f1);  //Creation of File Reader object
    BufferedReader br = new BufferedReader(fr); //Creation of BufferedReader object
    String s;

    while((s=br.readLine())!= null){
        words = s.split("\\.|\\?| \\*| [\\)]|-|;|\\p{Pd}|\"|:|,|_|!|'|[\\(]|[0-9]| ");

        for(String word : words){

            if(word.length() > 0) {
                h.insert(word);
            }


        }
    }
    fr.close();
   h.numberOfEnteries();
}

}// end HashTableImp
