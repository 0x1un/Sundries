package main

type Error interface {
	error
	Status() int
}

type StatusError struct {
	Code int
	Err  Error
}

func (se StatusError) Error() string {
	return se.Err.Error()
}

func (se StatusError) Status() int {
	return se.Code
}
