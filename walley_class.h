﻿/* 
 * File:   walley_class.h
 * Author: shd101wyy
 *
 * Created on September 18, 2012, 2:41 PM
 */

#include "walley_slice.h"



/*
 On Dec 4, I re-define the way of iteratre the class
 
 class a:
    def self.init(age=13):
        self.age=age
        println "Init a"
    def self.show():
        println self.age
 
 
 class b extends a:
    def self.init(age=14):
        super.init(age)
        println "Init b"
    def self.show():
        super.show()
 
 */



/*
 *Define a Class
 *
 * format:
 * class Hi:
 *     def showMessage(input_message):
 *         print("hello")
 * class Hello extends Hi:
 *     def showMessage2(input_message):
 *         print("hello2")
 *
 *x=Hello()
 *x.showMessage2("a")------>"hello2"
*/

/*
 * This  function is mainly to get the class name
 * eg className("class hello:")------>hello
 * eg className("class hello extends hi:")------>hello
 * !!!! class_name can not be 'extends' or 'class'
 */
char *className(char *input_str){
    input_str=trim(input_str);
    char *class_name;
    int begin=find_not_in_string(input_str,"class ")+6;
    int end;
    if(find_not_in_string(input_str," extends ")==-1){
        end=find_from_index(input_str,":",begin+1);
        if(end==-1){
            printf("@@ |%s|\n",CURRENT_INPUT_STR);
            printf("class define mistake occurred. please check.\nThe format should be 'class hi:' or 'class hi extends hello:");
            exit(0);
        }
        class_name=substr(input_str,begin,end);
        class_name=trim(class_name);
    }
    else{
        end=find_from_index(input_str," extends ",begin+1);
        class_name=substr(input_str,begin,end);
        class_name=trim(class_name);
    }
    return class_name;
}
/*
 * classMother is mainly to get what the class extends.
 * eg classMother("class hello:")------>"None"
 *    classMother("class hello extends hi:")------>"hi"
 */
char *classMother(char *input_str){
    input_str=trim(input_str);
    char *mother;
    if(find_not_in_string(input_str," extends ")==-1){
        mother="None";
    }
    else{
        int begin=find(input_str," extends ")+9;
        int end=find_from_index(input_str,":",begin+1);
        mother=substr(input_str,begin,end);
        mother=trim(mother);
    }
    return mother;
}


/*
 * eg x is hi()
 * add x to __instance_name__ in __walley__.wy
 */
//    0123
//("\n    exp",4)--->4
int space_ahead_for_formatStringInClass(char *string_in_class, int begin){
    int num=0;
    begin=begin-1;
    //printf("####\n|%s|\nbegin %d\n",string_in_class,begin);
    for (; begin>=0; begin--) {
        if (string_in_class[begin]==' ') {
            num++;
        }
        else{
            break;
        }
    }
    return num;
}

/*
 * This function now works without class extends
 * class hi:
 *     def showMessage(self):
 *         print("Hello")
 *
 * then after run I can get __temp_string_in_class_sentence__=""#Begin to define class...\ndef showMessage(self):\n    print("Hello")\n""
 * put that string to string_in_class as parameter.
 * eg formatStringInClass("__walley__.",hi",#Begin to define class...\ndef showMessage(self):\n    print("Hello")\n")
 *
 */

// This Function now is modified to change "self.age" to "x.age" directly
// Does not support "def show(self,age):" kind anymore
// The correct way of defining a class function should be
//                  "def self.show(age):"
/* The Annatation above is old*/
char *formatStringInClass(char *instance_name, char *string_in_class){
    int index_of_self=-1;
    //printf("INSTANCE_NAME %s\n",instance_name);
    string_in_class=toCString(string_in_class);

    
    // I forget what that is......
    while (TRUE) {
        index_of_self=find_from_index_not_in_string(string_in_class, "self.", index_of_self+1);
        if (index_of_self==-1) {
            break;
        }
        if (index_of_self==0||string_in_class[index_of_self-1]==' '||isSign(string_in_class[index_of_self-1])||isJudgeSign(string_in_class,index_of_self-1)) {
            string_in_class=replace_from_index_to_index(string_in_class, "self.", append(instance_name, "."), index_of_self, index_of_self+5);
        }
        
        
    }
    
    // I add code below on Feb 17 to solve self.stack[self.stack.length()] problem
    // change it to  x.stack[x.stack.length()]
    string_in_class=replace_not_in_string(string_in_class, "self.", append(instance_name, "."));
    
    int begin=0;
    int index_of_exp=0;
    int space_of_exp=0;
    while (TRUE) {
        index_of_exp=find_from_index_not_in_string(string_in_class, "    exp", begin);
        if (index_of_exp==-1) {
            break;
        }
        int index_of_gang_n=find_from_index_not_in_string(string_in_class, "\\n", index_of_exp+7);
        if (index_of_gang_n==-1) {
            break;
            //index_of_gang_n=(int)strlen(string_in_class);
        }
        if (find(substr(string_in_class, index_of_exp+7, index_of_gang_n), ":")==-1) {
            begin=index_of_gang_n+2;
            continue;
        }
        else {
            ///printf("Find expression");
            space_of_exp=space_ahead_for_formatStringInClass(string_in_class, index_of_exp+4);
            //printf("space_of_exp is %d\n",space_of_exp);
            int index_of_gang_n2=index_of_gang_n;
            char *instance_with_space=append(" ", append(instance_name," ")); //"x"-->" x "
            while (TRUE) {
                int a=index_of_gang_n2+2;
                int space_num=0;
                for (;a<(int)strlen(string_in_class); a++) {
                    //printf("|%c|\n",string_in_class[a]);
                    if (string_in_class[a]==' ') {
                        space_num++;
                    }
                    else{
                        break;
                    }
                }
                //printf("space num %d space_of_exp %d\n",space_num,space_of_exp);
                int begin2=a;
                index_of_gang_n2=find_from_index_not_in_string(string_in_class,"\\n", begin2);
                char *replace_str=substr(string_in_class, begin2-1, index_of_gang_n2);
                int begin3=find(replace_str," self ");
                if (space_num-4==space_of_exp) {
                    if (begin3!=0) {
                        printf("@@ |%s|\n",CURRENT_INPUT_STR);

                        printf("Mistake Occurred whiling defining expression in Class Functions\n'self 'must be added at the most ahead position\n");
                        exit(1);
                    }
                    else {
                        //printf("Begin replace\n");
                        string_in_class=replace_from_index_to_index(string_in_class," self " ,instance_with_space, begin2-1, index_of_gang_n2);
                        begin=index_of_gang_n2+2+(int)strlen(instance_with_space)-6;
                        index_of_gang_n2=index_of_gang_n2+(int)strlen(instance_with_space)-6;
                    }
                }
                else{
                    break;
                }
                
            }
            
        }
    }
    
    //printf("string_in_class |%s|\n",string_in_class);
    //string_in_class=replace(string_in_class, " self ", append(" ",append(instance_name," ")));
    return string_in_class;
}


/*
 * eg x is hi()
 * add x to __instance_name__ in VAR_var
 */
void addInstanceNameToVar(char ***instance_names_list,char *instance_name){
    Str_addString(instance_names_list, instance_name);
}

bool checkWhetherSameInstanceExistedFromVar(char **instance_names_list, char *instance_name){
    int length=Str_length(instance_names_list);
    int row=1;
    while (row<length) {
        if (strcmp(instance_names_list[row], instance_name)==0) {
            return TRUE;
        }
        row++;
    }
    return FALSE;
}


/*
 * get
 * class person:     //rohit is person
 * //def rohit.super.init(age)
 * def rohit.person.init(age)
 *     rohit.age=age
 *     print("person age is "+str(rohit.age))
 * 
 * rohit is Rohit() //Rohit extends person
 * formatStringInMotherClass("__walley__.wy","rohit","Rohit")
 */
// mother is a Walley_String



char *formatStringInAnyClassFromVar(struct VAR *struct_var, struct CLASS *class_list,char *instance_name, char *class_name) {
    //char *instance_name=son;
    //printf("\n\n#### formatStringInAnyClassFromFile ####\n");
   
    
    char *string_in_class =CLASS_stringInClass(class_list, class_name);
    
    char *mother=CLASS_classMother(class_list, class_name);
   
    char *output="";
    if (strcmp(toCString(mother), "None")!=0) {
        output=append(output, formatStringInAnyClassFromVar(struct_var,class_list,instance_name,mother));
    }
    //output=append(output, formatStringInClass(instance_name, string_in_class));
    output=append(output, toCString(string_in_class));

    int index_of_super=-1;
    while (TRUE) {
        index_of_super=find_from_index_not_in_string(output, "super.",index_of_super+1);
        if (index_of_super==-1) {
            break;
        }
        
        // It is function
        if (index_of_super==0 || output[index_of_super-1]==' ') {
            
            int current_space=0;
            int a=index_of_super-1;
            for (; a>=0; a--) {
                if (output[a]==' ') {
                    current_space++;
                }
                else{
                    break;
                }
            }
            
            int gang_n=find_from_index_not_in_string(output, "\\n", index_of_super+6);
            char *replace_str=substr(output, index_of_super, gang_n);
            //printf("replace str is |%s|\n",replace_str);
            
           
            char *string_in_mother_class=CLASS_stringInClass(class_list, mother);
            
            char *find_str_in_mother=replace_not_in_string(replace_str, "super.", "self.");
            find_str_in_mother=substr(find_str_in_mother, 0, find(find_str_in_mother,"(")+1);
            //printf("find_str_in_mother is |%s|\n",find_str_in_mother);
            
            int start=find_not_in_string(string_in_mother_class,find_str_in_mother);
            a=start;
            for (; a>=1; a--) {
                if (string_in_mother_class[a]=='n'&&string_in_mother_class[a-1]=='\\') {
                    break;
                }
            }
            //printf("start is %d\n",start);
            //printf("string_in_mother_class %s\n",string_in_mother_class);
            start=a+1;
            int end=start;
            while (TRUE) {
                end=find_from_index_not_in_string(string_in_mother_class, "\\n", end+1);
                if (end==-1) {
                    printf("@@ |%s|\n",CURRENT_INPUT_STR);

                    printf("Mistake occurred whiling calling function formatStringInAnyClassFromVar 1\n");
                    exit(1);
                }
                if (end+3>=(int)strlen(string_in_mother_class)||string_in_mother_class[end+3]!=' ') {
                    break;
                }
            }
            
            char *temp_str=substr(string_in_mother_class, start, end+2);
            temp_str=substr(temp_str, find_not_in_string(temp_str, "\\n")+2, (int)strlen(temp_str));
            //printf("temp_str now is |%s|\n",temp_str);
            
            char *with_str="";
            int gang_n2=-1;
            int start2=0;
        
            while (TRUE) {
                gang_n2=find_from_index_not_in_string(temp_str, "\\n", start2);
                if (gang_n2==-1) {
                    break;
                }
                char *temp2=substr(temp_str,start2, gang_n2);
                
                if (current_space==4) {
                    with_str=append(with_str, temp2);
                    with_str=append(with_str, "\\n");
                } else {
                    temp2=substr(temp2, 4, (int)strlen(temp2));
                    a=0;
                    for (; a<current_space; a++) {
                        temp2=append(" ", temp2);
                    }
                    with_str=append(with_str, temp2);
                    with_str=append(with_str, "\\n");
                }
                
                //printf("temp2-->|%s|\n",temp2);
                start2=gang_n2+2;
            }
            replace_str=substr(output, index_of_super-current_space, gang_n+2);
            //printf("replace str is |%s|\n",replace_str);
            //printf("with str is \n|%s|\n",with_str);
            //printf("OUTPUT IS \n|%s|\n",output);
            output=replace_from_index_to_index(output, replace_str, with_str, index_of_super-current_space, gang_n+2);
            // I didn't consider the expression situation like x=super.age......
        }
        else {
            continue;
        }
        
    }
    output=formatStringInClass(instance_name, output);
    //printf("$$$$$$$$output now is \n%s\n",output);
    
    return output;
    }

/*
 * class person:
    def init(self,age):
        self.age=age
        print("person age is "+str(self.age))
   class Rohit extends person:
    def init(self,age):
        super.init(self,age)
        print("Rohit age is "+str(self.age))
 * 
 * rohit is Rohit(16)
 *     ||
 *     ||
 *     \/
 * class Rohit extends person:
 * def rohit.init(age):
 *     //rohit.super.init(age)
 *     rohit.person.init(age)
 *     print("Rohit age is "+str(rohit.age))
 * 
 * class person:
 * def rohit.person.init(age)
 *     rohit.age=age
 *     print("person age is "+str(rohit.age))
 * 
 * 
 */
//formatStringInClassWithExtendFromFile("__walley__.wy","Rohit is person():")

char *formatStringInClassWithExtendFromVar(struct VAR *struct_var, struct CLASS *class_list,char *class_name,char *instance_name) {
    //printf("#### formatStringInClassWithExtendFromFile ####");
        
    char *mother=CLASS_classMother(class_list, class_name);
    char *string_in_class=CLASS_stringInClass(class_list, class_name);
    
    // has no extends
    if (strcmp("None", mother) == 0) {
        return formatStringInClass(instance_name, string_in_class);
    }
    // has extends
    else {
        return formatStringInAnyClassFromVar(struct_var,class_list,instance_name,class_name);
        
    }
}



bool checkWhetherSameClassExistedFromVar(struct CLASS *class_list, char *class_name){
    int length=CLASS_Length(class_list);
    int row=1;
    while (row<length) {
        if (strcmp(class_list[row].class_name, class_name)==0) {
            return TRUE;
        }
        row++;
    }
    return FALSE;
}



void copyInstanceValueToStructVar(struct VAR *struct_var,struct VAR **copy_to_var, char **instance_names_list){
    char *class_name;

    int length=Str_length(instance_names_list);
    
    int length_of_struct_var=Var_length(struct_var);
    int i=1;
    for(i=1;i<length;i++){
        class_name=instance_names_list[i];
        char *temp=append(class_name, ".");
        char *class_name2;
        if (find(class_name, "[")!=-1) {
            class_name2=substr(class_name, 0, find(class_name, "["));
        }
        else{
            class_name2="";
        }
        
        int j=0;
        for (; j<length_of_struct_var; j++) {
            if (find((struct_var+j)->var_name, temp)==0||strcmp(class_name, (struct_var+j)->var_name)==0 ||(strcmp(class_name2, "")!=0&&find((struct_var+j)->var_name, class_name2))==0) {
                // add it to copy_to_var
                Var_addProperty(copy_to_var,(struct_var+j)->var_name , (struct_var+j)->var_value, (struct_var+j)->var_type);
            }
        }
    }
}

void copyInstanceValueBackToVar(struct VAR *struct_var, struct VAR **copy_to_var,char **instance_names_list){
    int length=Str_length(instance_names_list);
    char *class_name;
    
    int length_of_struct_var=Var_length(struct_var);
    int i=1;
    for(;i<length;i++){
        class_name=instance_names_list[i];
        char *temp=append(class_name, ".");
        
        int j=0;
        for (; j<length_of_struct_var; j++) {
            if (find((struct_var+j)->var_name, temp)==0||strcmp(class_name, (struct_var+j)->var_name)==0) {
                // add it to copy_to_var
                Walley_Update_Var_And_Var_Value_To_Var(copy_to_var, (struct_var+j)->var_name, (struct_var+j)->var_value);
            }
        }
    }
}

