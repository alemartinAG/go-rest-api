package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

// Matrices structure containing all the matrices recieved from java program
type Matrices []struct {
	Matrix string  `json:"matrix"`
	Values [][]int `json:"values"`
}

// Recieves matrices and loads them into a structure
func recMatrices(w http.ResponseWriter, r *http.Request) {

	reqBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Fprintf(w, "ERROR")
	}

	responseString := string(reqBody)

	fmt.Printf("responseString: %s\n", responseString)

	var m Matrices

	err1 := json.Unmarshal([]byte(responseString), &m)
	if err1 != nil {
		log.Println(err)
		fmt.Fprintf(w, "ERROR")
	}

	fmt.Fprintf(w, "SUCCESS")

}

func fireTransition(w http.ResponseWriter, r *http.Request) {

}

func areEnabled(w http.ResponseWriter, r *http.Request) {

}

func main() {

	router := mux.NewRouter().StrictSlash(true)

	router.HandleFunc("/matrices", recMatrices).Methods("POST")
	router.HandleFunc("/fire", fireTransition).Methods("POST")
	router.HandleFunc("/enabled", areEnabled).Methods("POST")

	log.Fatal(http.ListenAndServe(":8080", router))

}
