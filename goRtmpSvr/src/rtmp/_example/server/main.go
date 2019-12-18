package main
//通常情况下，import的包都是相对$GOPATH/src目录引入的
/*
..\..\command_message.go:8:2: cannot find package "github.com/zhangpeihao/goamf" in any of:
	C:\Go\src\github.com\zhangpeihao\goamf (from $GOROOT)
	G:\RRRRRtc\rtmp\RtmpVS\goRtmpSvr\src\github.com\zhangpeihao\goamf (from $GOPATH) 这个是我新增的GOPATH
	C:\Users\zhangbin\go\src\github.com\zhangpeihao\goamf

执行这个就回可下载到我新增的GOPATH：
G:\RRRRRtc\rtmp\RtmpVS\goRtmpSvr>go get github.com/zhangpeihao/goamf

*/
import (
	"../../../rtmp"
	"flag"
	"log"
	"os"
)

var (
	revision string
)

func main() {
	var addr string
	flag.StringVar(&addr, "addr", "127.0.0.1:1935", `TCP address to listen on, ":1935" if empty`)
	flag.Parse()

	log.Printf("Serving RTMP on %s (rev-%s)", addr, revision)
	err := rtmp.ListenAndServe(addr)
	if err != nil {
		log.Printf("Got Error: %s", err)
		os.Exit(1)
	}
}
