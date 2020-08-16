use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;

my $d = HTTP::Daemon->new(
	   LocalAddr => 'localhost',
	   LocalPort => 1900,
	)|| die;

print "Please contact me at: <URL:", $d->url, ">\n";

while (my $c = $d->accept) {
	while (my $r = $c->get_request) {
	    if ($r->method eq 'GET') {
			my $uri = $r->uri;
			print $uri, "\n";

			if ($uri eq "/") {
				$uri = "/main.html";
			}

			my $file_s = "page".$uri;

			if ( -e $file_s) {
				$c->send_file_response($file_s);
			} else {
				$c->send_error(RC_NOT_FOUND);
			}
	    }
	    else {
			$c->send_error(RC_FORBIDDEN)
	    }
	}
}
