package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"

	"github.com/gorilla/mux"
	"gopkg.in/validator.v2"
)

type App struct {
	Router *mux.Router
}

type ShortenReq struct {
	url      string `json:"url" validate:"nonzero"`
	exp_time int64  `json:"expiration_in_minutes" validate:"min=0"`
}

type ShortlinkResp struct {
	shortLink string `json:"shortlink"`
}

func (a *App) Initalize() {
	log.SetFlags(log.LstdFlags)
	a.Router = mux.NewRouter()
	a.initalizeRoutes()
}

func (a *App) initalizeRoutes() {
	a.Router.HandleFunc("/api/shorten", a.createShortlink).Methods("POST") // post method
	a.Router.HandleFunc("/api/info", a.getShortlinkInfo).Methods("GET")
	a.Router.HandleFunc("/{shortlink:[a-zA-Z0-9]{1,10}}", a.redirect).Methods("GET")

}

func (a *App) createShortlink(w http.ResponseWriter, r *http.Request) {
	// convert the long links to short links
	var req ShortenReq
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondWithError(w, StatusError{http.StatusBadRequest, fmt.Errorf("parse parameters failed %v", r.Body)})
		return
	}

	if err := validator.Validate(req); err != nil {
		respondWithError(w, StatusError{http.StatusBadRequest, fmt.Errorf("validate parameters failed %v", r.Body)})
		return
	}
	defer r.Body.Close()
	fmt.Printf("%v\n", req)
}

func (a *App) getShortlinkInfo(w http.ResponseWriter, r *http.Request) {
	vals := r.URL.Query()
	s := vals.Get("shortlink")
	fmt.Printf("%v\n", s)
}

func (a *App) redirect(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	fmt.Printf("%v\n", vars["shortlink"])
}

func (a *App) Run(addr string) {
	log.Fatal(http.ListenAndServe(addr, a.Router))
}

func respondWithError(w http.ResponseWriter, err error) {
	switch e := err.(type) {
	case Error:
		log.Printf("HTTP %d - %s", e.Status(), e)
		respondWithJSON(w, e.Status(), e.Error())
	default:
		respondWithJSON(w, http.StatusInternalServerError, http.StatusText(http.StatusInternalServerError))
	}
}

func main() {
	a := App{}
	a.Initalize()
	a.Run(":8080")
}
