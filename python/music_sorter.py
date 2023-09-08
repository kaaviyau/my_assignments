import mysql.connector
a=mysql.connector.connect(host='localhost',user='root',passwd='Sample',database='musicdb')
if a.is_connected():
    pass
else:
    print('Connection failed. Please check your wifi. ')
b=a.cursor()

##########MAIN TABLE FUNCTIONS########

#To insert songs into the MAIN song table
def insert_songs():
    while True:
        name=input("Enter the name of the song: ")
        artist=input("Enter the artist of the song: ")
        ftartist=input("Enter the featured artist of the song: ")
        language=input("Enter the language of the song: ")
        album=input("Enter the album name: ")
        genre=input("Enter the genre: ")
        genre1=input("Enter genre1: (type s to skip) ")
        genre2=input("Enter genre2: (type s to skip) ")
        genre3=input("Enter genre3: (type s to skip) ")
        movie=input("Enter the movie: (type s to skip) ")
        length = input("Enter the song length: ")
        date=input("Enter the date released: ")
        if genre1=='s':
            genre1="NULL"
        if genre2=='s':
            genre2="NULL"
        if genre3=='s':
            genre3="NULL"
        if movie=='s':
            movie="NULL"
        try:   
            c="insert into main values('{}','{}','{}','{}','{}','{}','{}','{}','{}','{}',{},'{}',0,0)".format(name,artist,ftartist,language,album,genre,genre1,genre2,genre3,movie,length,date)
            b.execute(c)
            a.commit()
            print("The song", name, "has been added to the database\n")
            print('\n')
            u=input("Would you like to insert another song? (type y/n) ")
            if u in ('nN'):
                break
        except Exception:
            print("Please enter the correct values. ")
            print('\n')
        
    
#To delete songs from the MAIN song table
def delete_songs():
    while True:
        k=0
        name=input("Enter the song name to delete it: ")
        try:
            c="select * from MAIN where name = '{}'".format(name)
            b.execute(c)
            q=b.fetchall()
            if len(q)>0:
                c="delete from MAIN where name='{}'".format(name)
                b.execute(c)
                a.commit()
                print('The song ',name, 'has been deleted')
                ch=input("Would you like to continue? (y/n)")
                if ch in ('nN'):
                    break
            else:
                print('Sorry, this song is not available.')
                print('Please try again.')
                print('\n')
        except Exception:
            print('Error! Please try again.')
            print('\n')
            
#To update songs from the MAIN song table
def update_songs():
    while True:
        print("Which filter would you like to update?")
        print("(Filters available - 1. Artist, 2. Artist2, 3. Language, 4. Album, 5. Genre, 6. Genre1, 7. Genre2, 8. Genre3, 9. Movie, 10. Length, 11. Date_Released")
        try:
            fill = int(input("Enter the filter: "))
        except:
            fill=12
            print("Please try again")
        o=0
        if fill ==1:
            fill="artist"
            o=1
        elif fill==2:
            fill="artist2"
            o=0
        elif fill==3:
            fill="language"
            o=0
        elif fill==4:
            fill="album"
            o=0
        elif fill==5:
            fill="genre"
            o=0
        elif fill==6:
            fill="genre1"
            o=0
        elif fill==7:
            fill="genre2"
            o=0
        elif fill==8:
            fill="genre3"
            o=0
        elif fill==9:
            fill="movie"
            o=0
        elif fill==10:
            fill="length"
            o=0
        elif fill==11:
            fill="date_released"
            o=0
        else:
            print('Enter valid value')
            o=1
        if o==0:
            name = input("Enter the song name: ")
            change = input("Enter the new value you would like to update to:")
            try:
                c="select * from MAIN where name = '{}'".format(name)
                b.execute(c)
                x=b.fetchall()
                if len(x)>0:
                    c="update main set {}='{}' where name='{}'".format(fill,change,name)
                    b.execute(c)
                    a.commit()
                    print('The song ',name, 'has been updated')
                    ch=input("Would you like to continue? (y/n)")
                    if ch in ('nN'):
                        break
                else:
                    print('Sorry, this song is not available.')
                    print('Please try again.')
                    print('\n')
            except Exception:
                print('Error! Please try again.')
                print('\n')

#To select songs and filter them from the MAIN song table
def select_songs():
    while True:
        print("Which filter would you like to use to search?")
        print("1. Name\n2. Artist\n3. Language\n4. Album\n5. Genre\n6. Movie\n (type 1/2/3/4/5/6)")
        print("Press 0 to exit")
        try:
            x = int(input("Enter the filter: "))
        except:
            x=12
            print("Please try again")
            print('\n')
        if x==1:
            ch=input("Enter the song name: ")
            x="select * from MAIN where Name='{}'".format(ch)
            b.execute(x)
            q=b.fetchall()
            if len(q)>0:
                print("Name\t\tArtist\t\tArtist2\tLanguage\tAlbum\tGenre\tGenre1\tGenre2\tGenre3\tMovie\tLength\tDate Released\tViews\tLikes")
                for i in b.fetchall():
                    for j in i:
                        print(j, end="\t")
                y="update main set views = views+1 where name='{}'".format(ch)
                b.execute(y)
                print("\n")
                a.commit()
            else:
                print("Sorry! This song is not available. ")
                print('\n')
        if x==2:
            ch=input("Enter the artist name: ")
            x="select * from MAIN where Artist='{}' or Artist2='{}'".format(ch,ch)
            b.execute(x)
            q=b.fetchall()
            if len(q)>0:
                print("Name\t\tArtist\t\tArtist2\tLanguage\tAlbum\tGenre\tGenre1\tGenre2\tGenre3\tMovie\tLength\tDate Released\tViews\tLikes")
                for i in b.fetchall():
                    for j in i:
                        print(j, end="\t")
                    print("\n")
                y="update main set views = views+1 where artist='{}' or artist2='{}'".format(ch,ch)
                b.execute(y)
                print('\n')
                a.commit()
            else:
                print("Sorry! This artist is not available. ")
                print('\n')
        if x==3:
            ch=input("Enter the Language: ")
            x="select * from MAIN where Language='{}'".format(ch)
            b.execute(x)
            q=b.fetchall()
            if len(q)>0:
                print("Name\t\tArtist\t\tArtist2\tLanguage\tAlbum\tGenre\tGenre1\tGenre2\tGenre3\tMovie\tLength\tDate Released\tViews\tLikes")
                for i in b.fetchall():
                    for j in i:
                        print(j, end="\t")
                    print("\n")
                y="update main set views = views+1 where language='{}'".format(ch)
                b.execute(y)
                print("\n")
                a.commit()
            else:
                print("Sorry! This language is not available.")
                print('\n')
        if x==4:
            ch=input("Enter the Album: ")
            x="select * from MAIN where album='{}'".format(ch)
            b.execute(x)
            q=b.fetchall()
            if len(q)>0:
                print("Name\t\tArtist\t\tArtist2\tLanguage\tAlbum\tGenre\tGenre1\tGenre2\tGenre3\tMovie\tLength\tDate Released\tViews\tLikes")
                for i in b.fetchall():
                    for j in i:
                        print(j, end="\t")
                    print("\n")
                y="update main set views = views+1 where album='{}'".format(ch)
                b.execute(y)
                print("\n")
                a.commit()
            else:
                print("Sorry! This album is not available.")
                print('\n')
        if x==5:
            ch=input("Enter the Genre: ")
            x="select * from MAIN where Genre='{}' or Genre1='{}' or Genre2='{}' or Genre3='{}'".format(ch,ch,ch,ch)
            b.execute(x)
            q=b.fetchall()
            if len(q)>0:
                print("Name\t\tArtist\t\tArtist2\tLanguage\tAlbum\tGenre\tGenre1\tGenre2\tGenre3\tMovie\tLength\tDate Released\tViews\tLikes")
                for i in b.fetchall():
                    for j in i:
                        print(j, end="\t")
                    print("\n")
                y="update main set views = views+1 where genre='{}' or genre1='{}' or genre2='{}' or genre3='{}'".format(ch,ch,ch,ch)
                b.execute(y)
                print("\n")
                a.commit()
            else:
                print("Sorry! This genre is not available.")
                print('\n')
        if x==6:
            ch=input("Enter the Movie: ")
            x= "select * from MAIN where movie='{}'".format(ch)
            b.execute(x)
            q=b.fetchall()
            if len(q)>0:
                print("Name\t\tArtist\t\tArtist2\tLanguage\tAlbum\tGenre\tGenre1\tGenre2\tGenre3\tMovie\tLength\tDate Released\tViews\tLikes")
                for i in b.fetchall():
                    for j in i:
                        print(j, end="\t")
                    print("\n")
                y="update main set views = views+1 where movie='{}'".format(ch)
                b.execute(y)
                print("\n")
                a.commit()
            else:
                print("Sorry! This movie is not available.")
                print('\n')
        if x==0:
            break
        else:
            print("Please enter the correct value. ")
    print("\n")

   
########PLAYLISTS###############
#To Create a new table Playlist:
def createplay():
    while True:
        p=input('Enter name of the playlist which you would like to create: ')
        if p.isspace():
            print("Enter the playlist name as one word without spaces")
        try:
            c=("create table "+p+"(songname varchar(100))")
            b.execute(c)
            a.commit()
            print('The playlist',p,'has been successfully created!')
            print('\n')
            break
        except Exception:
            print("Please try again.")
            print("Enter the playlist name as one word without spaces")
            print('\n')

#To Insert song into Playlist:
def insertplay():
        try:
            p=input('Enter the name of the playlist where you would like to add songs: ')
            while True:
                song=input('Enter the name of the song that you would like to add the playlist: ')
                c=("insert into "+p+" values('{}')").format(song)
                b.execute(c)
                ch=input('Would you like to add another song? (type y/n) ')
                if ch in ('Nn'):
                    break
            a.commit()
            print('Songs successfully added to the playlist\n')
            print("\n")
        except:
            print("Error! Playlist not found.")
            insertplay()

#To Delete a song from Playlist: 
def delsong():
    try:
        p=input('Enter name of the playlist from which you want to delete a song:')
        s=input('Enter name of the song that you want to delete from your playlist:')
        c=("delete from "+p+" where songname='{}'").format(s)
        b.execute(c)
        a.commit()
        print('Song successfully deleted from playlist\n')
        print("\n")
    except:
        print("Error! Playlist not found.")
        delsong()

#To view a playlist:
def viewplay():
    try:
        p=input('Enter name of the playlist which you would like to view:')
        c=("select * from "+p+"")
        b.execute(c)
        print("Songs present in playlist",p)
        for i in b.fetchall():
            print(i[0])
        print("\n")
    except:
        print("Error! Playlist not found.")
        viewplay()
        
#To delete a playlist:
def delplay():
    try:
        p=input('enter name of the playlist which you want to delete:')
        c=("drop table "+p+"")
        b.execute(c)
        a.commit()
        print('playlist successfully deleted')
        print("\n")
    except:
        print("Error! Playlist not found.")
        delplay()

###################TOP SONGS####################
#to view top song chart by views
def tsviews():
    c="select name,artist,album,views,likes from main order by views desc"
    b.execute(c)
    f=0
    print("TOP 20 SONGS RANKED BY VIEWS")
    print("  Name\t\tArtist\tAlbum\tViews\tLikes")
    for i in b.fetchall():
        f+=1
        if f>20:
            break
        else:
            print (f, end='. ')
            for j in i:
                print(j, end="\t")
            print('\n')
    
#to view top song chart by likes
def tslikes():
    c="select name,artist,album,views,likes from main order by likes desc"
    b.execute(c)
    f=0
    print("TOP 20 SONGS RANKED BY LIKES")
    print("  Name\t\tArtist\tAlbum\tViews\tLikes")
    for i in b.fetchall():
        f+=1
        if f>20:
            break
        else:
            print (f, end='. ')
            for j in i:
                print(j, end="\t")
            print('\n')
#Ratings
def ratings():
    print(' 1.^0^(Excellent)','\n','2.^.^(Super)','\n','3.-_-(Good)','\n','4.>.<(Bad)','\n','5.>_<(Poor)','\n','6.Skip')
    while True:
        try:
            n=int(input('Rate AURA(1/2/3/4/5/6): '))
            if n>0 and n<6:
                c='update ratings set frequency=frequency+1 where rating={}'.format(n)
                b.execute(c)
                print('Thank You for your response')
                print('\n')
                break
            if n==6:
                print('Thank You for your response')
                print('\n')
                break
            else:
                print("Please enter 1/2/3/4/5/6")
        except:
            print("Please enter 1/2/3/4/5/6")
    
#feedback
def feedback():
    print("HAVE FEEDBACK? WE'D LOVE TO HEAR IT,BUT PLEASE DON'T SHARE SENSITIVE INFORMATION")
    x=input('TYPE HERE: ')
    print('Thank You for your response')
    c="insert into feedback values('{}')".format(x)
    b.execute(c)
    a.commit()
    print('\n')

#likes
def like_song():
    while True:
            k=0
            name=input("Enter the song name to like it: ")
            try:
                c="select * from MAIN where name = '{}'".format(name)
                b.execute(c)
                q=b.fetchall()
                if len(q)>0:
                    c="update MAIN set likes = likes+1 where name='{}'".format(name)
                    b.execute(c)
                    a.commit()
                    print('The song ',name, 'has been liked')
                    ch=input("Would you like to continue? (y/n)")
                    if ch in ('nN'):
                        break
                else:
                    print('Sorry, this song is not available.')
                    print('Please try again.')
                    print('\n')
            except Exception:
                print('Error! Please try again.')
                print('\n')
    
#############LOGIN & SIGN UP PAGE##################
def login_sign():
    while True:
        print('WELCOME TO AURA -- YOUR MUSIC DESTINATION !')
        print('1 - ADMIN')
        print('2 - USER')
        print('3 - EXIT')
        print("\n")
        try:
            k=int(input('Enter your choice: (1/2/3) '))
            if k==1 or k==2 or k==3:
                print('\n')
                break
            else:
                print("Please try again")
                print('\n')
        except:
            print("Please try again")
            print('\n')
    while True:
        if k==3:
            break
        elif k==2:
            g=input('Are you a new user ? (y/n) ')
            if g in ('Yy'):
                U=[]
                W=[]
                print("\n")
                print('SIGN IN:')
                username=input('Create an username: ')
                password=input('Create a password: ')
                email_id=input('Enter your Email ID: ')
                U.append(username)
                W.append(password)
                c="insert into user values('{}','{}','{}')".format(username,password,email_id)
                b.execute(c)
                a.commit()
                print('ACCOUNT SUCCESSFULLY CREATED')
                print("\n")
            if g in ('Nn'):
                print("\n")
                print('LOG IN:')
                while True:
                    if k==3:
                        break
                    username=input('Enter your username: ')
                    password=input('Enter your password: ')
                    x="select * from USER where username='{}'".format(username)
                    b.execute(x)
                    lst=b.fetchone()
                    print("\n")
                    if lst[1]==password:
                        if k==3:
                            break
                        print('Welcome back',username,'!')
                        print('\n')
                        while True:
                            print("1- Main table functions for users")
                            print("2- Playlist function for users")
                            print("3 - TOP SONGS")
                            print("4 - Exit")
                            try:
                                ch=int(input("Enter your choice: (1/2/3) "))
                                print('\n')
                                if ch==1:
                                    while True:
                                        print("Select an option: ")
                                        print("1. Select Songs 2. Like Songs 3. Exit (1/2) ")
                                        try:
                                            x= int(input("Enter your choice: "))
                                            print('\n')
                                            if x==1:
                                                select_songs()
                                                break
                                            if x==2:
                                                like_song()
                                                break 
                                            else:
                                                print("Please enter the correct value.")
                                                print('\n')
                                        except:
                                            print("Try again")
                                if ch==2:
                                    while True:
                                        print("Select an option: ")
                                        print("1. Create Playlist 2. Add songs 3. Delete Songs 4. View Playlist 5. Delete Playlist 6. Exit")
                                        try:
                                            x=int(input("Enter your choice: (1/2/3/4/5/6) "))
                                            print('\n')
                                            if x==1:
                                                createplay()
                                                break
                                            if x==2:
                                                insertplay()
                                                break
                                            if x==3:
                                                delsong()
                                                break
                                            if x==4:
                                                viewplay()
                                                break
                                            if x==5:
                                                delplay()
                                                break
                                            if x==6:
                                                continue
                                            else:
                                                print("Please enter the correct value.")
                                                print('\n')
                                        except:
                                            print("Try again")
                                            print('\n')
                                if ch==3:
                                    while True:
                                        print("Select an option: ")
                                        print("1. View Top Songs by Views 2. View Top Songs by Likes 3. Exit ")
                                        try:
                                            x=int(input("Enter your choice: (1/2/3) "))
                                            print('\n')
                                            if x==1:
                                                tsviews()
                                            if x==2:
                                                tslikes()
                                            if x==3:
                                                continue
                                            else:
                                                print("Please enter the correct value.")
                                                print('\n')
                                        except:
                                            print("Try again")
                                            print('\n')
                                if ch==4:
                                    k=3
                                    break
                                else:
                                    print("Please enter the correct value.")
                                    print('\n')
                            except:
                                print("Please enter the correct value")
                    else:
                        print('Invalid username or password! Please try again. ')
            if g not in ('yYnN'):
                print("Invalid entry! Try again")
                continue
        elif k==1:
            u=input('Enter the admin password: ')
            if u!='password':
                print('Invalid password! Please try again. ')
            else:
                print('Welcome back, Admin!')
                print('\n')
                while True:
                    print("1 - Main table functions for Admins ")
                    print("2 - Exit")
                    try:
                        q=int(input("Enter your choice: (1/2) "))
                        print('\n')
                        if q==1:
                            while True:
                                print("1. Insert Songs 2. Delete Songs 3. Update Songs 4. Select Songs 5.Exit")
                                try:
                                    x= int(input("Enter your choice: (1/2/3/4/5) "))
                                    print('\n')
                                    if x==1:
                                        insert_songs()
                                        break
                                    if x==2:
                                        delete_songs()
                                        break
                                    if x==3:
                                        update_songs()
                                        break
                                    if x==4:
                                        select_songs()
                                        break
                                    if x==5:
                                        break
                                except:
                                    print("Try again")
                                    print('\n')
                        if q==2:
                            k=3
                            break
                        else:
                            print("Try again")
                            print("\n")
                    except:
                        print("Try again")
                        print('\n')
        else:
            print('ENTER VALID CHOICE(1/2/3)')
while True:
    print('WELCOME TO AURA -- YOUR MUSIC DESTINATION !')
    print('MAIN MENU')
    print(' 1->LOGIN AND SIGN UP','\n','2->VIEW TOP SONGS CHART','\n','3->RATINGS AND FEEDBACK','\n','4->EXIT')
    try:
        n=int(input('PLEASE ENTER YOUR CHOICE(1/2/3/4): '))
        print('\n')
        if n==1:
            login_sign()
        elif n==2:
            while True:
                print(' 1->TOP SONGS BY VIEWS','\n','2->TOP SONGS BY LIKES','\n','3->MAIN MENU')
                try:
                    k=int(input('PLEASE ENTER YOUR CHOICE(1/2/3): '))
                    print('\n')
                    if k==1:
                        tsviews()
                    elif k==2:
                        tslikes()
                    elif k==3:
                        print('BACK TO MAIN MENU')
                        break
                    else:
                        print('ENTER VALID CHOICE')
                except:
                    print("Enter correct value.")
                    print('\n')
                
        elif n==3:
            while True:
                print(' 1->RATINGS','\n','2->FEEDBACK','\n','3->MAIN MENU')
                try:
                    n=int(input('PLEASE ENTER YOUR CHOICE(1/2/3): '))
                    print('\n')
                    if n==1:
                        ratings()
                    elif n==2:
                        feedback()
                    elif n==3:
                        print('BACK TO MAIN MENU')
                        break
                    else:
                        print('ENTER VALID CHOICE')
                except:
                    print("Try again")
                    print('\n')
        elif n==4:
            print('ARE YOU SURE YOU WANT TO EXIT AURA?')
            l=input('Y(YES)OR N(NO): ')
            if l in 'yY':
                print("Thank you for using AURA!")
                print('*'*50)
                break
            elif l in 'nN':
                print('BACK TO MAIN MENU')
            else:
                print('ENTER Y OR N ONLY')
        else:
            print('ENTER VALID CHOICE(1/2/3/4)')
            print('\n')
    except:
        print("Try again")
        print('\n')
            
        
    

                
