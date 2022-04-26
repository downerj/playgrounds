(format t "~{~@C~%~}"
				(mapcar #'code-char
								(loop for c from #x0 to #x10ffff collect c)))
