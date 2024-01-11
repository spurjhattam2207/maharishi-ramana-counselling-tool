#include "Node.h"
#include <assert.h>

Node::Node() {
    left = NULL;
    right = NULL;
    int book_code=0;
    int page=0;
    int paragraph=0;
    int sentence_no=0;
    int offset=0;
}
Node::Node(int b_code,int pg,int para){
    book_code=b_code;
    page=pg;
    paragraph=para;
    left = NULL;
    right = NULL;
    offset=0;
    sentence_no=0;
}
Node::Node(int b_code, int pg, int para, int s_no, int off){
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    offset = off;
}