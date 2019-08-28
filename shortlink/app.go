package main

import (
	"encoding/json"
	"fmt"
	"net/http"

	"github.com/go-playground/validator"
	"github.com/gorilla/mux"
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

func (a *App) initalizeRoutes() {
	a.Router.HandleFunc("/api/shorten", a.createShortlink).Methods("POST")
	a.Router.HandleFunc("/api/info", a.getShortlinkInfo).Methods("GET")
	a.Router.HandleFunc("/{shortlink:[a-zA-Z0-9]{1,10}}", a.redirect).Methods("GET")

}

func (a *App) createShortlink(w http.ResponseWriter, r *http.Request) {
	// convert the long links to short links
	var req ShortenReq
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		return
	}

	if err := validator.Validate(req); err != nil {
		return
	}
	defer r.Body.Close()
	fmt.Printf("%v\n", req)
}

func (a *App) getShortlinkInfo(w http.ResponseWriter, r *http.Request) {

}

func (a *App) redirect(w http.ResponseWriter, r *http.Request) {

}

func main() {

}
