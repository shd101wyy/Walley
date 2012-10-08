/* 
 * File:   walley_embed_function_library.h
 * Author: shd101wyy
 *
 * Created on September 6, 2012, 3:08 PM
 */

#include "walley_dictionary.h"
#include "math.h"
#include "time.h"


/*
 *function : to_int("'123'")----->"123" 
 *           to_int("12.3") ----->"12"
 *     
 */
char *to_int(char *input_str){
    input_str=removeAheadSpace(removeBackSpace(input_str));
    // string to int
    if(strcmp("string",variableValueType(input_str))==0) {
        input_str=substr(input_str,1,(int)strlen(input_str)-1);
        if(find(input_str,".")!=-1){
            input_str=substr(input_str,0,find(input_str,"."));
        }
        return input_str;
    }
    // double to int
    else if(strcmp("double",variableValueType(input_str))==0){
        input_str=substr(input_str,0,find(input_str,"."));
        return input_str;
    }
    // int to int
    else if (strcmp("int",variableValueType(input_str))==0){
        return input_str;
    }
    
    else {
        printf("Mistakes occurred while calling function to_int\nThe input_str %s is not string\nThis function only support string to int now\n",input_str);
        exit(1);
    }
}
/*
 *function : to_double("'123'")----->"123.0" 
 *function : to_double("'12.3'")----->"12.3" 
 */
char *to_double(char *input_str){
    input_str=trim(input_str);
    // string to double
    if (strcmp("string", variableValueType(input_str)) == 0) {
        input_str = substr(input_str, 1, (int) strlen(input_str) - 1);
        char *temp;
        if (find(input_str, ".") == -1) {
            temp = malloc(sizeof (char) *((int) strlen(input_str) + 3));
            strcat(temp, input_str);
            strcat(temp, ".0");
            temp[sizeof (char) *((int) strlen(input_str) + 3) - 1] = 0;
            input_str = temp;
        }
        return input_str;
    }
        // int to double
    else if (strcmp("int", variableValueType(input_str)) == 0) {
        char *temp;
        temp = malloc(sizeof (char) *((int) strlen(input_str) + 3));
        strcat(temp, input_str);
        strcat(temp, ".0");
        temp[sizeof (char) *((int) strlen(input_str) + 3) - 1] = 0;
        input_str = temp;
        return input_str;
    }
        // double to double
    else if (strcmp("double", variableValueType(input_str)) == 0) {
        return input_str;
    }
    
    else {
        printf("Mistakes occurred while calling function to_double\nThe input_str %s is not string\nThis function only support string to int now\n",input_str);
        exit(1);
    }
}
/*
 * function : to_num("'123'")------>123
 * function : to_num("123")------>123
 */
char *to_num(char *input_str){
    return to_double(input_str);
}

char *to_nstr(char *input_str){
    printf("#### to_nstr ####\n");
    if (strcmp("string", variableValueType(input_str)) == 0) {
        return toCString(input_str);
    }
    else {
        return input_str;
    }
}
/*
 *function : to_string("'123'")----->'123' string --> string just return
 *function : to_string("123")----->"12.3" 
 */
char *to_string(char *input_str){
    input_str=removeAheadSpace(removeBackSpace(input_str));
    if(strcmp("string",variableValueType(input_str))==0){
        return input_str;
    } else {
        char *temp;
        temp=malloc(sizeof(char)*((int)strlen(input_str)+3));
        strcat(temp,"'");
        strcat(temp,input_str);
        strcat(temp,"'");
        temp[sizeof(char)*((int)strlen(input_str)+3)-1]=0;
        
        return temp;
    }
}

char *simple_time(){
    time_t t;
    time(&t);
    //printf("%s",ctime(&t));
    char *temp=ctime(&t);
    temp=replace(temp,"\n","");
    return toString(temp);
}

char *walley_system(char *input_str){
    input_str=toCString(input_str);
    printf("\n\n####################################\n\n");
    system(input_str);
    printf("\n\n####################################\n\n");
    return "None";
}

char *math_sin(char *input_str){
    double num=atof(input_str);
    num=sin(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=malloc(sizeof(char)*(int)strlen(output));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    return output_str;
}
char *math_cos(char *input_str){
    double num=atof(input_str);
    num=cos(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=malloc(sizeof(char)*(int)strlen(output));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    return output_str;
}
char *math_tan(char *input_str){
    
    double num=atof(input_str);
    num=tan(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=malloc(sizeof(char)*(int)strlen(output));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    return output_str;
}
char *math_exp(char *input_str){
    double num=atof(input_str);
    num=exp(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=malloc(sizeof(char)*(int)strlen(output));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    return output_str;
}

char *math_log10(char *input_str) {
    double num = atof(input_str);
    num = log10(num);
    char output[100];
    sprintf(output, "%f", num);
    char *output_str = malloc(sizeof (char) *(int) strlen(output));
    int i = 0;
    for (i = 0; i < (int) strlen(output); i++) {
        output_str[i] = output[i];
    }
    return output_str;
}
/*
 * x=input() ---> input 10, then x is 10
 * x=input("--->") ---> print ---> at first and then input, input 10, get x = 10
 * 
 */
char *var_input(char *input_str) {
    if (stringIsEmpty(input_str)) {
        char *output = malloc(sizeof (char) *(100));
        gets(output);
        return output;
    }
    else{
        input_str=toCString(input_str);
        printf("%s",input_str);
        char *output = malloc(sizeof (char) *(100));
        gets(output);
        return output;
    }
}

/*
 * var_value_type("1")---->"int"
 */
char *var_value_type(char *input_str){
    char *type=malloc(sizeof(char)*(2+(int)strlen(variableValueType(input_str))));
    strcat(type,"'");
    strcat(type,variableValueType(input_str));
    strcat(type,"'");
    return type;
    //return variableValueType(input_str);
}

/*######################### Function for String ##################################################################################*/
//#################################################################################################################################
/*
 * x="Hello"  x.find("H").     x is user, "H" is find_str
 * eg string_find("Hello","H")----->0
 */
char *string_find(char *user,char* find_str){
    printf("#### x.find('hi') ####\n");
    user=substr(user,1,(int)strlen(user)-1);
    if(strcmp(variableValueType(find_str),"string")==0)
        find_str=substr(find_str,1,(int)strlen(find_str)-1);
    int index=find(user,find_str);
    char temp[100];
    sprintf(temp,"%d",index);
    char *output=malloc(sizeof(char)*(int)strlen(temp));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    return output;
}
/* x="Hello", x.find("Hello",1) now " "Hello", 1 " is parameter
 * eg string_find_from_index("'Hello'","'l',2")
 */
char *string_find_from_index(char *user, char *func_param){
    printf("#### eg x.find('hi',2) ####\n");
    user=substr(user,1,(int)strlen(user)-1);
    char *find_str=substr(func_param,0,find_not_in_string(func_param,","));
    find_str=removeAheadSpace(removeBackSpace(find_str));
    find_str=substr(find_str,1,(int)strlen(find_str)-1);
    char *from_index=substr(func_param,find_not_in_string(func_param,",")+1,(int)strlen(func_param));
    from_index=removeAheadSpace(removeBackSpace(from_index));
    int from=atoi(from_index);
    
    int index=find_from_index(user,find_str,from);
    printf("User is %s, find_str is %s, from %d\n",user,find_str,from);
        char temp[100];
    sprintf(temp,"%d",index);
    char *output=malloc(sizeof(char)*(int)strlen(temp));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    return output;
}
/* x="Hello", x.find("Hello",1) now " "llo","a" " is parameter
 * eg string_replace("'Hello'","llo","a")---->Hao
 */
char *string_replace(char *user, char *func_param){
    printf("#### eg x.replace('hi','i') ####\n");
    user=substr(user,1,(int)strlen(user)-1);
    char *replace_str=substr(func_param,0,find_not_in_string(func_param,","));
    replace_str=removeAheadSpace(removeBackSpace(replace_str));
    replace_str=substr(replace_str,1,(int)strlen(replace_str)-1);
    char *to_str=substr(func_param,find_not_in_string(func_param,",")+1,(int)strlen(func_param));
    to_str=removeAheadSpace(removeBackSpace(to_str));
    to_str=substr(to_str,1,(int)strlen(to_str)-1);
    printf("user %s, replace str %s, to_str %s\n",user,replace_str, to_str);
    char *output=replace(user,replace_str,to_str);  
    printf("-------> output is %s\n",output);
    char *output2=malloc(sizeof(char)*((int)strlen(output)+2));
    strcat(output2,"'");
    strcat(output2,output);
    strcat(output2,"'");
    return output2;  
}
/*
 * x="Hello"  x.count("l")-------->2
 * string_count_str("'Hello'","'l'")
 */
char *string_count_str(char *user, char *func_param){
    user=substr(user,1,(int)strlen(user)-1);
    func_param=substr(func_param,1,(int)strlen(func_param)-1);
    int num=count_str(user,func_param);
    char temp[100];
    sprintf(temp,"%d",num);
    char *output=malloc(sizeof(char)*(int)strlen(temp));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    return output;
}
/*
 * x="Hello"  x.length()----->5
 * string_length("Hello")
 */
char *string_length(char *user){
    printf("#### string_length ####\n");
    printf("### input_str %s ###\n",user);
    user=toCString(user);
    int length=(int)strlen(user);
    //length=length-2; // delete '' and ""
    char temp[100];
    sprintf(temp,"%d",length);
    char *output=malloc(sizeof(char)*(int)strlen(temp));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    printf("output %s\n",output);
    return output;
}

char *string_isdigit(char *user){
    user=toCString(user);
    bool is_digit=stringIsDigit(user);
    if (is_digit==TRUE) {
        return "TRUE";
    }
    else{
        return "FALSE";
    }
}

char *string_isalpha(char *user){
    user=toCString(user);
    bool is_alpha=stringIsAlpha(user);
    if (is_alpha==TRUE){
        return "TRUE";
    }
    else{
        return "FALSE";
    }
}

char *string_toupper(char *user){
    user=toCString(user);
    user=stringToUpperCase(user);
    return toString(user);
}

char *string_tolower(char *user){
    printf("#### string_tolower ####\n---->%s\n",user);
    user=toCString(user);
    user=stringToLowerCase(user);
    return toString(user);
}

/*
 * x="  Hello "  x.trim()---->"Hello"
 * string_trim("'Hello'")
 */
char *string_trim(char *user){
    user=trim(user);
    user=substr(user,1,(int)strlen(user)-1);
    char *output=trim(user);
    char *output2=malloc(sizeof(char)*((int)strlen(output)+2));
    strcat(output2,"'");
    strcat(output2,output);
    strcat(output2,"'");
    return output2;  
}

/*#################### Function for List ############################*/

/*
 * eg x=[1,2,3] x.append(5)---->x=[1,2,3,5]
 * list_append("[1,2,3]","4"]
 */
char *list_append(char *user, char *func_param){
    printf("#### list_append #### x.append(4) ####\n");
    char *output=listAppendOneElement(user,func_param);
    printf("#### list is |%s| ####\n",output);
    return output;
}
/*
 * eg x=[1,2,3] x.remove_at_index([0])------->x=[2,3]
 *    x=[1,[1,2],4] x.remove_at_index([1])------->x=[1,4]
 * list_remove_at_index("[1,2,3]","[0]")------->[2,3]
 */
char *list_remove_at_index(char *user, char *func_param){
    printf("#### list_remove_at_index #### x.remove_at_index([0])\n");
    return listRemoveOneElementAtOneIndex(user,func_param);
}
/*
 * range(0,10)------->[0,1,2,3,4,5,6,7,8,9]
 */
char *list_range(char *function_param){
    
}

/*
 * list_length
 * eg: x=[1,2,[3,4],5].    x.length()=4  x[2].length()=2
 */
char *list_length(char *user){
    char temp[100];
    int num=valueNumOfList(user);
    sprintf(temp,"%d",num);
    char *output=malloc(sizeof(char)*(int)strlen(temp));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    return output;
}
/*
 * list_remove_element
 * x=[1,2,3] x.remove(1)--->[2,3]
 * x=[1,2,3,1] x.remove(1)--->[2,3]
 * x=[1,[1],2] x,remove(1)--->[2]
 */
char *list_remove_element(char *user, char *function_param){
    return listRemoveOneElementByValue(user,function_param);
}

/*################## Function for Dictionary ############################*/
/*
 * x={a:1,b:2}  x.key()=[a.b]
 * dict_key("{a:1,b:2}")-------->"[a,b]"
 * 
 */
char *dict_key(char *user){
    return keyOfDictionaryAsList(user);
}

//################## Function for File Operation ###########################
// file_readline("'math.wy'") and return list form of string
char *file_readlines(char *walley_file_name){
    walley_file_name=toCString(walley_file_name);
    printf("#### file_readlines ####\n");
    FILE *fp=fopen(walley_file_name,"r");
    if(fp==NULL){
        printf("Mistake occurred whiling calling function file_readlines\nDoes not find %s\n",walley_file_name);
        fclose(fp);
        exit(0);
    }
    else{
        char output[100000]="";
        strcat(output,"[");
        char arr[1000] = "";
        
        while (fgets(arr, 1000, fp) != NULL) {
            char temp[1000];
            int a=0;
            for(a=0;a<(int)strlen(arr);a++){
                if(arr[a]=='\n')
                        break;
                else
                    temp[a]=arr[a];
            }
            char *temp2=substr(temp,0,(int)strlen(arr));
            strcat(output, "\"");
            //strcat(output, arr);
            //strcat(output,temp);
            strcat(output,temp2);
            strcat(output, "\",");
        }
        //printf("%s****************\n\n\n",output);
        output[(int) strlen(output)-1]=']';
        int length=(int)strlen(output);
        char *output2=malloc(sizeof(char)*(length+1));
        int i=0;
        for(i=0;i<(int)strlen(output);i++){
            output2[i]=output[i];
        }
        output2[(int)strlen(output2)]=0;
        //printf("%s****************\n\n\n",output);
        fclose(fp);
        //output2=substr(output2,0,length);
        printf("OUTPUT2 %s\n",output2);
        return output2;
    }
}
// file_writelines("'walley.wy','str to file'")
char *file_writelines(char *file_name,char *lines){
    printf("#### file_writelines ####\n");
    printf("-- %s -- %s --\n",file_name,lines);
    //printf("parameters is %s\n",params);
    //params=trim(params);
    //char *file_name=substr(params,0,find_not_in_string(params,","));
    //char *lines=substr(params,find_not_in_string(params,",")+1,(int)strlen(params));
    file_name=toCString(file_name);
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL){
        printf("Mistake occurred whiling calling function file_writelines\nNo file %s found",file_name);
        fclose(fp);
        exit(1);
    }
    else{
        fputs(lines,fp);
        fclose(fp);
        return "None";
    }
}

char *file_removefile(char *file_name){
    file_name=trim(file_name);
    file_name=toCString(file_name);
    remove(file_name);
    return "None";
}

char *file_createfile(char *file_name){
    printf("#### file_createfile ####\n");
    file_name=trim(file_name);
    file_name=toCString(file_name);
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL){
        printf("Failed to create %s\n",file_name);
        exit(0);
    }
    //else {
    //    fputs("#~",fp);
    //}
    fclose(fp);
    return "None";
}
//################## Special Function Summary #############################*/

char *Walley_Run_Special_Function(char *function, char *file_var_name) {
    //################### Special Function #########################################################
    /*
     * eg x="Hello"-----> x.find("He")----->0
     */
    char *return_value;

    printf("Begin to run special function like x=[1,2,3]  x.append(12)\n");
    printf("---->Function %s\n---->file_var_name %s\n",function,file_var_name);
    // eg x="Hello"  x.find("Hi")
    char *user = substr(function, 0, find_not_in_str_list_dict_parenthesis(function, ".")); //------> x
    char *user_function = substr(function, find_not_in_str_list_dict_parenthesis(function, ".") + 1, (int) strlen(function)); // -------->find("Hi")
    char *user_value; //= getValueFromValueName(file_var_name, user); // ------->x="Hello"
    if (checkWhetherSameVarNameExistsFromFile(file_var_name, user)==TRUE) {
        user_value = getValueFromValueName(file_var_name, user);
    } else {
        user_value=user;
    }
    char *user_function_parameter = substr(user_function, find(user_function, "(") + 1, (int) strlen(removeBackSpace(user_function)) - 1); // ----->"Hi"  which is inside parenthesis
    int num_of_params = numOfParameters(user_function_parameter);
    printf("user---->%s\nuser_function---->%s\nuser_value---->%s\nuser_function_parameter %s\n---->num_of_param %d\n",user,user_function,user_value,user_function_parameter,num_of_params);
    // Special function for String
    if (strcmp("string", variableValueType(user_value)) == 0) {
        if (find(user_function, "find(") == 0) {
            if (num_of_params == 1)
                return_value = string_find(user_value, user_function_parameter);
            else if (num_of_params == 2)
                return_value = string_find_from_index(user_value, user_function_parameter);
        } else if (find(user_function, "replace(") == 0) {
            return_value = string_replace(user_value, user_function_parameter);
        } else if (find(user_function, "count(") == 0) {
            return_value = string_count_str(user_value, user_function_parameter);
        } else if (find(user_function,"length(")==0){
            printf("****** %s\n",user_value);
            return_value=string_length(user_value);
        } else if (find(user_function,"trim(")==0){
            return_value=string_trim(user_value);
        } else if (find(user_function,"isdigit(")==0){
            return_value=string_isdigit(user_value);
        } else if (find(user_function,"isalpha(")==0){
            return_value=string_isalpha(user_value);
        } else if (find(user_function,"toupper(")==0){
            return_value=string_toupper(user_value);
        } else if (find(user_function,"tolower(")==0){
            return_value=string_tolower(user_value);
        }
        else {
            printf("This Special Function for String eg. x.find('x') is still under development\n");
        }
    }        // Special function for list
    else if (strcmp("list", variableValueType(user_value)) == 0) {
        if (find(user_function, "append(") == 0) {
            printf("#### FIND APPEND\n");
            return_value = list_append(user_value, user_function_parameter);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, user, return_value);
            printf("#### FINISH APPEND ####\n");
        } else if (find(user_function, "remove_at_index(") == 0) {
            return_value = list_remove_at_index(user_value, user_function_parameter);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, user, return_value);
        } else if (find(user_function, "length(") == 0) {
            return_value = list_length(user_value);
        }
        else if (find(user_function,"remove_element(")==0){
            return_value= list_remove_element(user_value,user_function_parameter);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, user, return_value); 
        }
    }        // Special function for dictionary
    else if (strcmp("dictionary", variableValueType(user_value)) == 0) {
        if (find(user_function, "key(") == 0) {
            return_value = dict_key(user_value);
        } else if (find(user_function, "keys(") == 0) {
            return_value = dict_key(user_value);
        }
    }

    return return_value;
}