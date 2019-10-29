package main

/*
#cgo CFLAGS: -g -Wpedantic -Wall
#include <stdlib.h>
#include "cuda.h"
*/
import "C"

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"unsafe"

	"github.com/gorilla/mux"
)

const OK = "SUCCESS"
const ER = "ERROR"


func recvMatrices(w http.ResponseWriter, r *http.Request) {

	reqBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Fprintf(w, "Kindly enter data with the event title and description only in order to update")
	}

	responseString := string(reqBody)

    str := C.CString(responseString)
	success := C.pass_json(str)

	C.free(unsafe.Pointer(str))

	vector := [4]bool{true, false, true, false}

	vectorJson, err := json.Marshal(vector)
    if err != nil {
        log.Fatal("Cannot encode to JSON ", err)
    }

	if success{
		C.printMatrices()
		fmt.Fprintf(w, "{\"status\":\"%s\", \"vector\":%s}", OK, vectorJson)
	} else {
		fmt.Fprintf(w, "{\"status\":\"%s\", \"vector\":%v}", ER, vectorJson)
	}
}

func fireTransition(w http.ResponseWriter, r *http.Request) {

	vector := [4]bool{true, false, true, false}

	vectorJson, err := json.Marshal(vector)
    if err != nil {
        log.Fatal("Cannot encode to JSON ", err)
    }

	fmt.Fprintf(w, "{\"status\":\"%s\", \"vector\":%v}", OK, vectorJson)
		
}

func main() {

	router := mux.NewRouter().StrictSlash(true)
	
	router.HandleFunc("/matrices", recvMatrices).Methods("POST")
	router.HandleFunc("/fire", fireTransition).Methods("POST")

	log.Fatal(http.ListenAndServe(":8080", router))
}

