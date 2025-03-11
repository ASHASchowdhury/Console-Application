using System;
public class todoList{
    public static string[] tasks=new string[10];
    public static int taskcount=0;
    
    public static void addtask(){
        Console.WriteLine("Enter a new task: ");
        tasks[taskcount]=Console.ReadLine();
        taskcount++;
    }
    
    public static void viewtask(){
        for(int i=0;i<taskcount;i++){
            Console.WriteLine((i+1)+"."+ tasks[i]);
        }
    }
    
    public static void completetask(){
        Console.WriteLine("Enter the number of the task to mark as complete:");
        int tasknumber=int.Parse(Console.ReadLine())-1;
        
        if(tasknumber>=0 && tasknumber<taskcount){
            tasks[tasknumber]=tasks[tasknumber]+"(completed)";
            Console.WriteLine("Marked as Completed");
        }
        else{
            Console.WriteLine("Invalid task Number.");
        }
    }
    
    public static void Main(string[] args){
        bool running =true;
        while(running){
            Console.WriteLine("What would you like to do?");
            Console.WriteLine("1. Add a task");
             Console.WriteLine("2. View tasks");
              Console.WriteLine("3. Mark a task as complete");
               Console.WriteLine("4. exit");
               
               string choice =Console.ReadLine();
               switch(choice){
                   case "1":
                   addtask();
                   break;
                   case "2":
                   viewtask();
                   break;
                   case "3":
                   completetask();
                   break;
                    case "4":
                   running=false;
                   break;
                   default:
                   Console.WriteLine("Invalid choice.please try again.");
                   break;
               }
        }
    }
}
