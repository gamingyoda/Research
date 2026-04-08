/*---------------------------------

  output function  2d

----------------------------------*/
void PostFlow_output(int time){
  char fn[50];
  FILE *fpw;
  int i, j, r0, n, xi, eta, ns, nv, ii;
  int Sij;
  int num;
  double mach, alp, re, Qt;
  int istep;

  /*************保存量の計算************************/
  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	Q[n][0][r0] = rho[n][r0] * S[n][r0];
	Q[n][1][r0] = rho[n][r0] * ux[n][r0] * S[n][r0];
	Q[n][2][r0] = rho[n][r0] * uy[n][r0] * S[n][r0];
	Q[n][3][r0] = e[n][r0] * S[n][r0];
      }
    }
  }

  for(n=0;n<NT;n++){
    sprintf(fn,"./out_wcns2/postFlow[%d][%d]",n,time);

    fpw = fopen(fn,"wb");

    if(NULL==fpw){
      perror(fn);
      exit(1);
    }

    num = sizeof(int) * 2;
    xi  = it[n] - 1;
    eta = jt[n] - 1;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&xi,sizeof(int),1,fpw);
    fwrite(&eta,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);

    num = sizeof(double) * 3 + sizeof(int) * 1;
    mach = 0.0;
    alp = 0.0;
    re = 0.0;
    istep = 0;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&mach,sizeof(double),1,fpw);
    fwrite(&alp,sizeof(double),1,fpw);
    fwrite(&re,sizeof(double),1,fpw);
    fwrite(&istep,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);


    Sij = xi * eta;
    num = sizeof(double) * 4 * Sij;

    fwrite(&num,sizeof(int),1,fpw);
    for(ii=0;ii<4;ii++){
      for(j=0;j<jt[n]-1;j++){
	for(i=0;i<it[n]-1;i++){
	  r0 = dim[n](i, j);
	  Qt = Q[n][ii][r0] / S[n][r0];
	  fwrite(&Qt,sizeof(double),1,fpw);
	}
      }
    }
    fwrite(&num,sizeof(int),1,fpw);

    num = sizeof(int) * 2;
    ns  = 3;
    nv  = 0;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&ns,sizeof(int),1,fpw);
    fwrite(&nv,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);

    Sij = xi * eta;
    num = sizeof(double) * Sij;

    fwrite(&num,sizeof(int),1,fpw);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
    	r0 = dim[n](i, j);
    	fwrite(&k_turb[n][r0],sizeof(double),1,fpw);
      }
    }
    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
    	r0 = dim[n](i, j);
    	fwrite(&omega[n][r0],sizeof(double),1,fpw);
      }
    }
    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);
    for(j=0;j<jt[n]-1;j++){
      for(i=0;i<it[n]-1;i++){
	r0 = dim[n](i, j);
	fwrite(&Mut[n][r0],sizeof(double),1,fpw);
      }
    }
    fwrite(&num,sizeof(int),1,fpw);

    num = sizeof(double) * nv * Sij;

    fwrite(&num,sizeof(int),1,fpw);
    fwrite(&num,sizeof(int),1,fpw);


    fclose(fpw);
  }

}
