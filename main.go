package main

/*
#cgo CFLAGS: -g -Wall
#include <stdlib.h>
#include "loop.h"
*/
import "C"

import (
	//"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"unsafe"
	//"strings"
	//"strconv"

	"github.com/gorilla/mux"
)



/*type Matrix []struct {
	Type    string `json:"matrix"`
	Values 	[][]int32 `json:"values"`
}*/

type Matrix []struct {
	Type    string 	`json:"matrix"`
	Values 	string 	`json:"values"`
	Rows  	string 	`json:"rows"`
	Columns string 	`json:"columns"`
}


/*func homeLink(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "put your values in /compute!")
}*/

func putValue(w http.ResponseWriter, r *http.Request) {

	reqBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Fprintf(w, "Kindly enter data with the event title and description only in order to update")
	}

	responseString := string(reqBody)

    /*data := Matrix{}
    json.Unmarshal([]byte(responseString), &data)

    for i := 0; i < len(data); i++ {
    	fmt.Println("Type: ", data[i].Type)
    	fmt.Println("Value: ", data[i].Values)

    }

    fmt.Println("------------------------------------")
  
    for i := 0; i < len(data); i++ {
    	
	    str := C.CString(data[i].Type)
		C.pass_json(str)
		str = C.CString(data[i].Values)
		C.pass_json(str)
		str = C.CString(data[i].Rows)
		C.pass_json(str)
		str = C.CString(data[i].Columns)
		C.pass_json(str)
		C.free(unsafe.Pointer(str))
		
    	//fmt.Println("Type: ", data[i].Type)
    }*/

    
    /*rows := C.int(len(data[0].Values))
    columns := C.int(len(data[0].Values[0]))*/
    //matr := (**C.int)(unsafe.Pointer(&data[0].Values[0][0]))

    str := C.CString(responseString)
	C.pass_json(str)
	C.free(unsafe.Pointer(str))

	C.printMatrices()



	

    //C.loop()

	fmt.Fprintf(w, "Recibido Cabeza\n")

}

func main() {

	router := mux.NewRouter().StrictSlash(true)
	//router.HandleFunc("/", homeLink)
	router.HandleFunc("/", putValue).Methods("POST")
	log.Fatal(http.ListenAndServe(":8080", router))
}

