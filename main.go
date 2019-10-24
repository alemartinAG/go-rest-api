package main

/*
#cgo CFLAGS: -g -Wall
#include <stdlib.h>
#include "loop.h"
*/
import "C"

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	//"strings"
	//"strconv"

	"github.com/gorilla/mux"
)



type Matrix []struct {
	Type    string `json:"matrix"`
	Values 	[][]int `json:"values"`
}


func homeLink(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "put your values in /compute!")
}

func putValue(w http.ResponseWriter, r *http.Request) {

	reqBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Fprintf(w, "Kindly enter data with the event title and description only in order to update")
	}

	responseString := string(reqBody)

    data := Matrix{}
    json.Unmarshal([]byte(responseString), &data)
    
    for i := 0; i < len(data); i++ {
    	fmt.Println("Type: ", data[i].Type)
    }

	fmt.Fprintf(w, "Recibido Cabeza\n")

}

func main() {

	router := mux.NewRouter().StrictSlash(true)
	router.HandleFunc("/", homeLink)
	router.HandleFunc("/compute", putValue).Methods("POST")
	log.Fatal(http.ListenAndServe(":8080", router))
}
