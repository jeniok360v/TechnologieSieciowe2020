use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;

my $d = HTTP::Daemon->new(
       LocalAddr => 'localhost',
       LocalPort => 1900,
   )|| die;

print "Please contact me at: <URL:", $d->url, ">\n";


while (my $c = $d->accept) {
    print "0";
    while (my $r = $c->get_request) {
        if ($r->method eq 'GET') {
            print "1";
            $file_s= "index.html";    # index.html - jakis istniejacy plik
            $c->send_file_response($file_s);
        }
        else {
            print "2";
            $c->send_error(RC_FORBIDDEN)
        }

    }
  $c->close;
  undef($c);
}