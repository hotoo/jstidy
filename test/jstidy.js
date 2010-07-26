/**
 * @overview this is file summary infomation.
 * @author 闲耘™ (mail[AT]xianyun.org)
 * @version 2009/12/22
 */

/*
 * This is
 * muilt line
 * comments for following function.
 */
function test(arg1,arg2){
    // this is single line comment.
    window.alert("0\"");
    var num = 2 / 4, reg = /re/img, s = "this is single line string";

    // following is hard number for test slash(/).
    // do not translate it to regular expression.
    // and more single line comments.

    /* some multiline comments
     * at new line.
     */

    /* more and more multiline comments
     * after another multiline comments.
     */
    var n2 = 2
        /
        4;
    var r2 = // this is comment.
        /reg/img;
    var d = new Date();

    var a = [0, 1, 2, 3, 4, 5, 6];
    if(true){
        alert(a.join(""));
    }
}

//javascript
var reg = /**//[\/][/][*]([\S\s]*?)(?:[*][/;\[\]]|$)|[\/][/g;//](.*)|\"((?:\\\\|\\"|[^"///])*)"|'((?:\\\\|\\'|[^'\//;])*)'/gi;

reg = 0;
reg = 2 / 1, /**///
/**///
/**/
//
reg = /reg/ 1;

var num1 = 0.541;

function f(test) {
    return (test/*
    /* //
    ' "
    { ;
    \*/ && // /* // " ' { ; \
    test &&
    " /* // \
    \" ' \
    { ;" &&
    ' /* // \
    " \' \
    { ;' &&
    test);
}
