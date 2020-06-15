#include <idc.idc>

//////////////////////////////////////////////////////////////////////////////

static str_replace(orig, rep, with) {
    auto result; // the return string
    auto len_rep;  // length of rep

    auto searcher;
    auto next;
    
    if (orig == "")
        return;
        
    result = "";
    searcher = orig;
        
    len_rep = strlen(rep);
    next = 0;
    
    while (next != -1)
    {
        next = strstr(searcher, rep);
        if (next == -1)
            break;
        result = result + substr(searcher, 0, next) + with;
        searcher = substr(searcher, next + len_rep, -1);
    }
    
    result = result + searcher;

    return result;
}

// --------------------------------

// Main conversion routine
static ExportFunctionComments(H_File_Name)
{
    auto i, total, total_funcs;

    auto hh;  // output file handle
    
    auto func_addr, func_rcmt, func_cmt, func_name;
    func_addr = 0;
    
    //str_replace("DOG DOG DOG", " ", "CAT");
    
    if ((hh=fopen(H_File_Name,"w")) == 0)
    {
        Warning("Couldn't open file '%s'!",H_File_Name);
        return -1;
    }
    
    writestr(hh, "static main()\n{\n");
    
    while (func_addr != -1)
    {
        func_addr = NextFunction(func_addr);
        if (func_addr == -1)
            break;
            
        //Message("Next function at %x (%s)\n", func_addr, GetFunctionName(func_addr));
        func_rcmt = GetFunctionCmt(func_addr, 1);
        func_rcmt = str_replace(func_rcmt, "\"", "\\\"");
        func_rcmt = str_replace(func_rcmt, "\n", "\\n\\\n");
        func_cmt = GetFunctionCmt(func_addr, 0);
        func_name = GetFunctionName(func_addr);
        /*if (func_rcmt != "")
            Message("-----\nRCmt:\n\n%s\n", func_rcmt);*/
        if (func_cmt != "")
            Message("-----\nCmt:\n\n%s\n", func_cmt);
        total_funcs++;
        
        if (func_rcmt != "")
        {
            writestr(hh, form("    // %s\n    SetFunctionCmt(0x%x, \n        \"%s\", 1);\n\n", func_name, func_addr, func_rcmt));
            total++;
        }
    }

    writestr(hh, "}\n");
    
    fclose(hh);

    Message("%d funcs found.\n", total_funcs);
    Message("Successful %d elements exported.\n",total);
    return 0;
}

static main()
{
    ExportFunctionComments("ImportGeneratedFunctionComments.idc");
}