import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, date
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    username = session["username"]
    history_rows = db.execute("SELECT * FROM stocks WHERE username = ?", username)

    return render_template("index.html", rows=history_rows, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        shares = (request.form.get("shares"))
        if request.form.get("shares") == None:
            return apology("Invalid quantity", 400)
        elif not shares.isdigit():
            return apology("You cannot purchase partial shares.", 400)
        else:
            try:
                search = lookup(request.form.get("symbol"))
                username = session["username"]
                today = date.today()
                d = today.strftime("%d/%m/%Y")
                symbol = search["symbol"]
                name = search["name"]
                shares = int((request.form.get("shares")))
                price = float(search["price"])
                total = price * shares
                print(total)
                buy = db.execute("INSERT INTO stocks (username, symbol, name, shares, price, total, date) VALUES(?, ?, ?, ?, ?, ?, ?)", username, symbol, name, shares, price, total, d)

                flash('Bought!')
                return redirect("/")

            except TypeError:
                return apology("invalid symbol, try again. TypeError", 400)
            except ValueError:
                return apology("invalid symbol, try again. ValueError", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username = session["username"]
    history_rows = db.execute("SELECT * FROM stocks WHERE username = ?", username)
    return render_template("history.html", rows=history_rows, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # a symbol is submitted
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 400)
        else:
            try:
                search = lookup(request.form.get("symbol"))
                name = search["name"]
                price = usd(search["price"])
                symbol = search["symbol"]
                return render_template("quoted.html", name=name, price=price, symbol=symbol)
            except:
                TypeError
                return apology("invalid symbol try again", 400)


     #User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        #Ensure confirmation matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords must match", 400)

        # Add new user to database for username sndf hashed pw
         #Access form data
        username = request.form.get("username")
        password = request.form.get("password")
        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist, then add new user to db
        if len(rows) > 0:
            return apology("Username already exists!", 400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return render_template("sell.html")
